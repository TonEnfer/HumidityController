/*
 * LedDisplay.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include "stm32f0xx.h"

class LedDisplay {
public:
	LedDisplay();
	void init();
	void show(uint8_t);
	void off();
};

#endif /* LEDDISPLAY_H_ */
