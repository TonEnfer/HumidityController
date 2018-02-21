/*
 * GPIO.h
 *
 *  Created on: 18 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stm32f0xx.h>
#include <sys/_stdint.h>

namespace HAL {

class GPIO {
public:
	static void pinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource,
			uint8_t GPIO_AF);
	static uint8_t readInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
};

} /* namespace HAL */

#endif /* GPIO_H_ */
