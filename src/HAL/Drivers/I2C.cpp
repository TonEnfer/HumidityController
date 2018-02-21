/*
 * I2Cclass.cpp
 *
 *  Created on: 6 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/GPIO.h>
#include <HAL/Drivers/I2C.h>
#include <stm32f0xx.h>

namespace HAL {

void I2C_class::init(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;	// Alternative function
	GPIOA->OTYPER |= GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10;	// open drain
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR9_1
			| GPIO_OSPEEDR_OSPEEDR10_0 | GPIO_OSPEEDR_OSPEEDR10_1;	// max speed
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0; //pull up

	HAL::GPIO::pinAFConfig(GPIOA, 9, 4);	// I2C1_SCL
	HAL::GPIO::pinAFConfig(GPIOA, 10, 4);	// I2C1_SDA

	I2C_BUS->CR1 |= I2C_CR1_SWRST;
	I2C_BUS->CR1 &= I2C_CR1_SWRST;

	I2C_BUS->CR1 &= ~I2C_CR1_PE;
	while (I2C_BUS->CR1 & I2C_CR1_PE) {
	};
	I2C_BUS->TIMINGR |= (0xB << I2C_OFFSET_TIMINGR_PRESC)
			| (0x13 << I2C_OFFSET_TIMINGR_SCLL)
			| (0xF << I2C_OFFSET_TIMINGR_SCLH)
			| (0x4 << I2C_OFFSET_TIMINGR_SCLDEL)
			| (0x2 << I2C_OFFSET_TIMINGR_SDADEL);

	I2C_BUS->CR1 |= I2C_CR1_PE;
	while ((I2C_BUS->CR1 & I2C_CR1_PE) == 0) {
	};
}

void I2C_class::startDirectionAdressSize(I2C_Direction Direction,
		uint8_t Adress, uint8_t Size) {

	uint32_t tempreg = I2C_BUS->CR2;

	if (Direction)
		tempreg |= I2C_CR2_RD_WRN;
	else {
		tempreg &= ~I2C_CR2_RD_WRN;
		I2C_BUS->ISR |= I2C_ISR_TXE;
	}

	tempreg |= I2C_CR2_AUTOEND;
	tempreg &= ~I2C_CR2_RELOAD;

	tempreg &= ~I2C_CR2_NBYTES;
	tempreg |= (Size << I2C_OFFSET_CR2_NBYTES) & I2C_CR2_NBYTES;

	tempreg &= ~I2C_CR2_SADD;
	tempreg |= (Adress & I2C_CR2_SADD);
	I2C_BUS->CR2 = tempreg;

	I2C_BUS->CR2 |= I2C_CR2_START;
}

void I2C_class::stop(void) {

	if (!(I2C_BUS->ISR & I2C_ISR_STOPF)) {
		//if no stop flag is present;
		//making a stop condition
		I2C_BUS->CR2 |= I2C_CR2_STOP;
		while (I2C_BUS->ISR & I2C_ISR_BUSY)
			;
	}
	I2C_BUS->ICR |= I2C_ICR_STOPCF;
	I2C_BUS->ICR |= I2C_ICR_NACKCF;

	if (I2C_BUS->ISR & (I2C_ISR_ARLO | I2C_ISR_BERR)) {
		I2C_BUS->ICR |= I2C_ICR_ARLOCF;
		I2C_BUS->ICR |= I2C_ICR_BERRCF;
	}
}

I2C_Status I2C_class::write(uint8_t addr, uint8_t *data, uint8_t size) {
	while ((I2C_BUS->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY)
		;
	startDirectionAdressSize(I2C_Transmitter, addr, size);
	for (uint8_t i = 0; i < size; i++) {
		while ((I2C_BUS->ISR & I2C_ISR_TXIS) == 0) {
			if ((I2C_BUS->ISR & I2C_ISR_NACKF))
				return I2C_ERROR;
		};
		I2C_BUS->TXDR = data[i];
	}
	for (volatile uint32_t i = 0;; i++) {
		if ((I2C_BUS->ISR & I2C_ISR_STOPF))
			break;
		if (i >= 0xFFFFFFF)
			return I2C_ERROR;
	}
	stop();
	return I2C_SUCCESS;
}

I2C_Status I2C_class::read(uint8_t addr, uint8_t *data, uint8_t size) {
	startDirectionAdressSize(I2C_Receiver, addr, size);
	asm("nop");
	asm("nop");
	for (volatile uint8_t i = 0; i < size; i++) {
		while ((I2C_BUS->ISR & I2C_ISR_RXNE) == 0)
			;
		volatile uint8_t val = I2C_BUS->RXDR;
		data[i] = val;
	}
	for (volatile uint32_t i = 0;; i++) {
		if ((I2C_BUS->ISR & I2C_ISR_STOPF))
			break;
		if (i >= 0xFFFFFFF)
			return I2C_ERROR;
	}
	stop();
	return I2C_SUCCESS;
}

I2C_class I2C = I2C_class();
} /* namespace HAL */
