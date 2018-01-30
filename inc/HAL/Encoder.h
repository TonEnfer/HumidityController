/*
 * encoder.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f0xx.h"

class Encoder {
public:
	Encoder();
	bool press();
	bool longPress();
	bool rotate();
	int getPosition();
private:
	bool pres = false;
	bool longPres = false;
	bool rotation = false;
	int position = 0;
};

#endif /* ENCODER_H_ */
