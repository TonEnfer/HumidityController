/*
 * GPIO.h
 *
 *  Created on: 18 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <main.h>
namespace HAL {

class GPIO {
public:
	static void pinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource,
			uint8_t GPIO_AF);
};

} /* namespace HAL */

#endif /* GPIO_H_ */
