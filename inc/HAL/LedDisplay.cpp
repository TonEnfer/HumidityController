/*
 * LedDisplay.cpp
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/LedDisplay.h>

LedDisplay::LedDisplay() {

}

void LedDisplay::init() {

}

void LedDisplay::show(uint8_t number) {
	if(number > 99)
	{}
	else
	{}
}

void LedDisplay::off() {
	this->show(100);
}
