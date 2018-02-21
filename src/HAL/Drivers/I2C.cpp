/*
 * I2Cclass.cpp
 *
 *  Created on: 6 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/I2C.h>
#include <stm32f0xx.h>
#include <sys/_stdint.h>

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
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0;
	// ����� �������������� �������
	HAL::GPIO::pinAFConfig(GPIOA, 9, 1);	// I2C1_SCL
	HAL::GPIO::pinAFConfig(GPIOA, 10, 1);	// I2C1_SDA

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

void I2C_class::startDirectionAdressSize(I2C_Direction Direction,
		uint8_t Adress, uint8_t Size) {
	Display.show(2);

	if (Direction)
		I2C_BUS->CR2 |= I2C_CR2_RD_WRN;
	else
		I2C_BUS->CR2 &= ~I2C_CR2_RD_WRN;
	I2C_BUS->CR2 &= ~I2C_CR2_NBYTES;
	I2C_BUS->CR2 |= Size << I2C_OFFSET_CR2_NBYTES;
	I2C_BUS->CR2 &= ~I2C_CR2_SADD;
	I2C_BUS->CR2 |= Adress;
	I2C_BUS->CR2 |= I2C_CR2_START;

	while ((I2C_BUS->ISR & I2C_ISR_BUSY) == 0)
		;
}

void I2C_class::stop(void) {
	Display.show(3);
	I2C_BUS->CR2 |= I2C_CR2_STOP;
	while (I2C_BUS->ISR & I2C_ISR_BUSY)
		;

	I2C_BUS->ICR |= I2C_ICR_STOPCF;
	I2C_BUS->ICR |= I2C_ICR_NACKCF;

	if (I2C_BUS->ISR & (I2C_ISR_ARLO | I2C_ISR_BERR)) {
		I2C_BUS->ICR |= I2C_ICR_ARLOCF;
		I2C_BUS->ICR |= I2C_ICR_BERRCF;
	}
}

I2C_Status I2C_class::write(uint8_t addr, uint8_t *data, uint8_t size) {
	startDirectionAdressSize(I2C_Transmitter, addr, 1 + size);
	for (uint8_t i = 0; i < size; i++) {
		while ((I2C_BUS->ISR & I2C_ISR_TXIS) == 0) {
			if ((I2C_BUS->ISR & I2C_ISR_NACKF))
				return I2C_ERROR;
		};
		I2C_BUS->TXDR = data[i];
	}
	if ((I2C_BUS->ISR & I2C_ISR_TC) != 0)
		return I2C_ERROR;
	stop();
	return I2C_SUCCESS;
}

I2C_Status I2C_class::read(uint8_t addr, uint8_t *data, uint8_t size) {
	startDirectionAdressSize(I2C_Receiver, addr, size);
	for (uint8_t i = 0; i < size; i++) {
		while ((I2C_BUS->ISR & I2C_ISR_RXNE) != 1)
			;
		*(data++) = I2C_BUS->RXDR;
	}
	if ((I2C_BUS->ISR & I2C_ISR_TC) != 0)
		return I2C_ERROR;
	stop();
	return I2C_SUCCESS;
}

I2C_class I2C = I2C_class();
} /* namespace HAL */
