/*
 * GPIO.cpp
 *
 *  Created on: 18 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/GPIO.h>

namespace HAL {
void GPIO::pinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource,
		uint8_t GPIO_AF) {
	uint32_t temp = 0x00;
	uint32_t temp_2 = 0x00;

	temp = ((uint32_t)(GPIO_AF)
			<< ((uint32_t)((uint32_t) GPIO_PinSource & (uint32_t) 0x07) * 4));
	GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t) 0xF
			<< ((uint32_t)((uint32_t) GPIO_PinSource & (uint32_t) 0x07) * 4));
	temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
	GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

uint8_t GPIO::readInputDataBit(GPIO_TypeDef* GPIOx,
			uint16_t GPIO_Pin) {
		uint8_t bitstatus = 0x00;
		if ((GPIOx->IDR & GPIO_Pin) != (uint32_t) 0) {
			bitstatus = (uint8_t) 1;
		} else {
			bitstatus = (uint8_t) 0;
		}
		return bitstatus;
	}

}
/* namespace HAL */
