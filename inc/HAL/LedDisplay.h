/*
 * LedDisplay.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_
namespace HAL {
#include "stm32f0xx.h"

class LedDisplay {
public:
	LedDisplay();
	void init();
	void show(uint8_t);
	void off();
};
extern LedDisplay Display;
}
#endif /* LEDDISPLAY_H_ */
