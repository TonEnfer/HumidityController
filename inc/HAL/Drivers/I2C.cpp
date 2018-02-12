/*
 * I2Cclass.cpp
 *
 *  Created on: 6 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/I2C.h>

namespace HAL {

I2C_class::I2C_class(I2C_TypeDef* I2Cx) {
	this->I2Cx = I2Cx;
}

I2C_Status I2C_class::waitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_Event) {
//	volatile uint32_t wait = I2C_WAIT_TIMEOUT;
//	uint32_t reg;
//
//	while (wait--) {
//		reg = I2Cx->ISR;
//		//reg |= I2Cx->SR2 << 16;
//		reg &= I2C_FLAG_MASK;
//		if ((reg & I2C_Event) == I2C_Event)
//			return I2C_SUCCESS;
//	}

	return I2C_ERROR;
}
I2C_Status I2C_class::waitFlagSet(I2C_TypeDef* I2Cx, uint32_t I2C_Flag) {
//	volatile uint32_t wait = I2C_WAIT_TIMEOUT;
//	volatile uint16_t *preg;
//
//	// Determine which I2C register to be read
//	preg = (I2C_Flag & 0x80000000) ? &(I2Cx->ISR) : &(I2Cx->SR2);
//	I2C_Flag &= 0xFFFF;
//
//	// Wait for flag to be set
//	while (wait--) {
//		if (*preg & I2C_Flag)
//			return I2C_SUCCESS;
//	}
//
	return I2C_ERROR;
}
I2C_Status I2C_class::waitFlagReset(I2C_TypeDef* I2Cx, uint32_t I2C_Flag) {
//	volatile uint32_t wait = I2C_WAIT_TIMEOUT;
//	volatile uint16_t *preg;
//
//	// Determine which I2C register to be read
//	preg = (I2C_Flag & 0x80000000) ? &(I2Cx->ISR) : &(I2Cx->SR2);
//	I2C_Flag &= 0xFFFF;
//
//	// Wait until flag cleared
//	while (wait--) {
//		if (!(*preg & I2C_Flag))
//			return I2C_SUCCESS;
//	}
//
	return I2C_ERROR;
}

I2C_Status I2C_class::write(const uint8_t* buf, uint32_t nbytes,
		uint8_t SlaveAddress, I2C_STOP_TypeDef stop) {
//	// Initiate a START sequence
//	I2Cx->CR2 |= I2C_CR2_START;
//	// Wait for EV5
//	if (waitEvent(I2Cx, I2C_EVENT_EV5) == I2C_ERROR)
//		return I2C_ERROR;
//
//	// Send the slave address (EV5)
//	I2Cx->TXDR = SlaveAddress & ~(0x0001); // Last bit be reset (transmitter mode)
//
//	// Wait for EV6
//	if (waitEvent(I2Cx, I2C_EVENT_EV6) == I2C_ERROR)
//		return I2C_ERROR;
//
//	// Send first byte (EV8)
//	I2Cx->TXDR = *buf++;
//	// Send rest of data (if present)
//	while (--nbytes) {
//		// Wait for BTF flag set
//		if (waitFlagSet(I2Cx, I2C_F_BTF) == I2C_ERROR)
//			return I2C_ERROR;
//		// Transmit byte via I2C
//		I2Cx->TXDR = *buf++;
//	}
//	// Wait for BTF flag set
//	if (waitFlagSet(I2Cx, I2C_F_BTF) == I2C_ERROR)
//		return I2C_ERROR;
//
//	// Transmission end
//	if (stop == I2C_STOP) {
//		// Generate a STOP condition
//		I2Cx->CR2 |= I2C_CR2_STOP;
//		// Wait for a STOP flag
//		if (waitFlagReset(I2Cx, I2C_F_STOPF) == I2C_ERROR)
//			return I2C_ERROR;
//	}
//
	return I2C_SUCCESS;
}

I2C_Status I2C_class::read(uint8_t *buf, uint32_t nbytes, uint8_t SlaveAddress)
{
//	// Enable Acknowledgment
//		I2Cx->CR1 |= I2C_CR1_ACK;
//		// Clear POS flag
//		I2Cx->CR1 &= ~I2C_CR1_POS; // NACK position current
//
//		// Initiate START sequence
//		I2Cx->CR2 |= I2C_CR2_START;
//		// Wait for EV5
//		if (waitEvent(I2Cx,I2C_EVENT_EV5) == I2C_ERROR) return I2C_ERROR;
//
//		// Send the slave address (EV5)
//		I2Cx->TXDR = SlaveAddress | (0x00FE); // Last bit set (receiver mode)
//
//		// Wait for EV6
//		if (waitFlagSet(I2Cx,I2C_F_ADDR) == I2C_ERROR) return I2C_ERROR;
//
//		// There are can be three cases:
//		//   read 1 byte
//		//   read 2 bytes
//		//   read more than 2 bytes
//		if (nbytes == 1) {
//			// Receive 1 byte (AN2824 figure 2)
//			I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ACK); // Disable I2C acknowledgment
//
//			// EV6_1 must be atomic operation (AN2824)
//			__disable_irq();
//			(void)I2Cx->SR1; // Clear ADDR bit
//			(void)I2Cx->SR2;
//			I2Cx->CR2 |= I2C_CR2_STOP; // Generate a STOP condition
//			__enable_irq();
//
//			// Wait for RxNE flag (receive buffer not empty) EV7
//			if (waitFlagSet(I2Cx,I2C_F_RXNE) == I2C_ERROR) return I2C_ERROR;
//
//			// Read received byte
//			*buf = (uint8_t)I2Cx->RXDR;
//		} else if (nbytes == 2) {
//			// Receive 2 bytes (AN2824 figure 2)
//			I2Cx->CR1 |= I2C_CR1_POS; // Set POS flag (NACK position next)
//
//			// EV6_1 must be atomic operation (AN2824)
//			__disable_irq();
//			(void)I2Cx->SR2; // Clear ADDR bit
//			I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ACK); // Disable I2C acknowledgment
//			__enable_irq();
//
//			// Wait for BTF flag set (byte transfer finished) EV7_3
//			if (waitFlagSet(I2Cx,I2C_F_BTF) == I2C_ERROR) return I2C_ERROR;
//
//			// This should be atomic operation
//			__disable_irq();
//			// Generate a STOP condition
//			I2Cx->CR1 |= I2C_CR1_STOP;
//			// Read first received byte
//			*buf++ = (uint8_t)I2Cx->DR;
//			__enable_irq();
//
//			// Read second received byte
//			*buf = (uint8_t)I2Cx->DR;
//		} else {
//			// Receive more than 2 bytes (AN2824 figure 1)
//			(void)I2Cx->SR2; // Clear ADDR bit
//
//			// Read received bytes into buffer
//			while (nbytes-- != 3) {
//				// Wait for BTF (cannot guarantee 1 transfer completion time)
//				if (waitFlagSet(I2Cx,I2C_F_BTF) == I2C_ERROR) return I2C_ERROR;
//				*buf++ = (uint8_t)I2Cx->DR;
//			}
//
//			// Wait for BTF flag set (byte transfer finished) EV7_2
//			if (waitFlagSet(I2Cx,I2C_F_BTF) == I2C_ERROR) return I2C_ERROR;
//
//			// Disable the I2C acknowledgment
//			I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ACK);
//
//			__disable_irq();
//			// Read received byte N-2
//			*buf++ = (uint8_t)I2Cx->RXDR;
//			// Generate a STOP condition
//			I2Cx->CR1 |= I2C_CR1_STOP;
//			__enable_irq();
//
//			// Read received byte N-1
//			*buf++ = I2Cx->RXDR;
//
//			// Wait for last byte received
//			if (waitEvent(I2Cx,I2C_EVENT_EV7) == I2C_ERROR) return I2C_ERROR;
//
//			// Read last received byte
//			*buf = (uint8_t)I2Cx->RXDR;
//		}
//
//		// Wait for a STOP flag
//		if (waitFlagReset(I2Cx,I2C_F_STOPF) == I2C_ERROR) return I2C_ERROR;
//
		return I2C_SUCCESS;
}

I2C_class I2C = I2C_class(I2C1);
} /* namespace HAL */
