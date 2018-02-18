/*
 * I2Cclass.cpp
 *
 *  Created on: 6 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/I2C.h>

namespace HAL {

/*
 ��������� ��������� ��������� ����.
 ����������� �����, �������������� �������.
 ����������� �������� ��� ������ ����.
 */
void I2C_class::init(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;		// ������� ������������ I2C
	// ��������� ��� PB6, PB7
	GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;	// ����� �������������� �������
	GPIOA->OTYPER |= GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10;// �������� ���������
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9 | GPIO_OSPEEDR_OSPEEDR10;// ������������ ��������
	// ����� �������������� �������
	HAL::GPIO::pinAFConfig(GPIOB, 6, 1);	// I2C1_SCL
	HAL::GPIO::pinAFConfig(GPIOB, 6, 1);	// I2C1_SDA

	I2C_BUS->CR1 &= ~I2C_CR1_PE;			// �������� I2C
	while (I2C_BUS->CR1 & I2C_CR1_PE) {
	};	// ��� ���� ����������

	// ������� ������������ ������ I2C = 48 ���
	// ������� ���� I2C = 100 kHz
	// ���������� ��������
	I2C_BUS->TIMINGR |= (0xB << I2C_OFFSET_TIMINGR_PRESC)
			| (0x13 << I2C_OFFSET_TIMINGR_SCLL)
			| (0xF << I2C_OFFSET_TIMINGR_SCLH)
			| (0x4 << I2C_OFFSET_TIMINGR_SCLDEL)
			| (0x2 << I2C_OFFSET_TIMINGR_SDADEL);

	I2C_BUS->CR1 |= I2C_CR1_PE;					// ������� I2C
	while ((I2C_BUS->CR1 & I2C_CR1_PE) == 0) {
	};	// ��� ���� ���������
}

/*
 ��� ��������� �������, ������������ � �� �����.
 ������������� ����������� ������ - ���� ��� ��������.
 ����� ����� ������������ ������.
 ����� ����� �������� ����������.
 ����� ����� �� ����.
 ���������:
 Direction - ����������� (0-��������, 1-����)
 Adress - ����� �������� ����������
 Size - ������ ������ (�� 1 �� 255 ����)
 */
void I2C_class::startDirectionAdressSize(I2C_Direction Direction,
		uint8_t Adress, uint8_t Size) {
	//I2C_BUS->CR2 &= ~I2C_CR2_AUTOEND;				// �������� ���� �������
	//I2C_BUS->CR2 &= ~I2C_CR2_RELOAD;				// �� ������������ ����� ������������
	if (Direction)
		I2C_BUS->CR2 |= I2C_CR2_RD_WRN;	// ����� �����
	else
		I2C_BUS->CR2 &= ~I2C_CR2_RD_WRN;			// ����� ��������
	I2C_BUS->CR2 &= ~I2C_CR2_NBYTES;				// �������� ������ ������
	I2C_BUS->CR2 |= Size << I2C_OFFSET_CR2_NBYTES;	// ���������� ������ ������
	I2C_BUS->CR2 &= ~I2C_CR2_SADD;	// �������� ����� �������� ����������
	I2C_BUS->CR2 |= Adress;			// ���������� ����� �������� ����������
	I2C_BUS->CR2 |= I2C_CR2_START;					// ������ ����� �� ����
	while ((I2C_BUS->ISR & I2C_ISR_BUSY) == 0) {
	};	// ������� ������ ������
}

/*
 ��� ��������� �������, ������������ � �� �����.
 ����� ���� �� ����.
 ������� �����.
 ��������� ������� ������, ������� ����� ������.
 */
void I2C_class::stop(void) {
	I2C_BUS->CR2 |= I2C_CR2_STOP;				// ������ ���� �� ����
	while (I2C_BUS->ISR & I2C_ISR_BUSY) {
	};		// ������� ������ �����
	// ������ ����� - ���������� ��� ���������� ������ ����
	I2C_BUS->ICR |= I2C_ICR_STOPCF;		// STOP ����
	I2C_BUS->ICR |= I2C_ICR_NACKCF;		// NACK ����
	// ���� ���� ������ �� ���� - ������ �����
	if (I2C_BUS->ISR & (I2C_ISR_ARLO | I2C_ISR_BERR)) {
		I2C_BUS->ICR |= I2C_ICR_ARLOCF;
		I2C_BUS->ICR |= I2C_ICR_BERRCF;
	}
}

/*
 ��������� ���������� ������ Size ���� � ������� Register �� ������ Adress.
 ���������:
 Adress - ����� �������� ����������
 Register - �������, � ������� ����� �������� ������
 Data - ��������� ������ ����� ������ ��� ��������
 Size - ������� ���� ����� �������� (�� 1 �� 254)
 ����������:
 1 - ���� ������ ������� ��������
 0 - ���� ��������� ������
 */
I2C_Status I2C_class::write(uint8_t addr, uint8_t reg, uint8_t *data,
		uint8_t size) {
	uint8_t Count = 0;	// ������� ������� ���������� ����
	// �����
	startDirectionAdressSize(I2C_Transmitter, addr, 1 + size);
	// ������ ���� I2C �������� ������ ���� ��� ��������,
	// ���� ������� NACK-����, ��������� � ���, ��� ���������� �� ��������.
	// ���� ������� NACK-����, �������� ����������.
	while ((((I2C_BUS->ISR & I2C_ISR_TXIS) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
	};
	if (I2C_BUS->ISR & I2C_ISR_TXIS)
		I2C_BUS->TXDR = reg;	// ��������� ����� ��������

	// ���������� ����� �� ��� ���, ���� �� ������� TC-����.
	// ���� ������� NACK-����, �������� ����������.
	while ((((I2C_BUS->ISR & I2C_ISR_TC) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
		if (I2C_BUS->ISR & I2C_ISR_TXIS)
			I2C_BUS->TXDR = *(data + Count++);	// ��������� ������
	}
	stop();
	if (Count == size)
		return I2C_SUCCESS;
	return I2C_ERROR;
}

/*
 ��������� ���������� ������ Size ���� �� �������� Register �� ������ Adress.
 ���������:
 Adress - ����� �������� ����������
 Register - �������, �� �������� ����� ������� ������
 Data - ��������� ���� ���������� �������� ������
 Size - ������� ���� ����� ������� (�� 1 �� 255)
 ����������:
 1 - ���� ������ ������� �������
 0 - ���� ��������� ������
 */
I2C_Status I2C_class::read(uint8_t addr, uint8_t reg, uint8_t *data,
		uint8_t size) {
	uint8_t Count = 0;	// ������� ������� �������� ����
	// �����
	startDirectionAdressSize(I2C_Transmitter, addr, 1);
	// ������ ���� I2C �������� ������ ���� ��� ��������,
	// ���� ������� NACK-����, ��������� � ���, ��� ���������� �� ��������.
	// ���� ������� NACK-����, �������� ����������.
	while ((((I2C_BUS->ISR & I2C_ISR_TC) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
		if (I2C_BUS->ISR & I2C_ISR_TXIS)
			I2C_BUS->TXDR = reg;	// ��������� ����� ��������
	}
	// ��������� �����
	startDirectionAdressSize(I2C_Receiver, addr, size);
	// ��������� ����� �� ��� ���, ���� �� ������� TC-����.
	// ���� ������� NACK-����, ���� ����������.
	while ((((I2C_BUS->ISR & I2C_ISR_TC) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
		if (I2C_BUS->ISR & I2C_ISR_RXNE)
			*(data + Count++) = I2C_BUS->RXDR;	// �������� ������
	}
	stop();
	if (Count == size)
		return I2C_SUCCESS;
	return I2C_ERROR;
}

I2C_class I2C = I2C_class();
} /* namespace HAL */
