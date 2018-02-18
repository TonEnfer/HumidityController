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

}
/* namespace HAL */
