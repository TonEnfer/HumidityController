/*
 * encoder.cpp
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <HAL/Encoder.h>
namespace HAL {
Encoder_class::Encoder_class() {
	// TODO Auto-generated constructor stub

}

bool Encoder_class::press() {
	bool tmp = this->pres;
	this->pres = false;
	return tmp;
}

bool Encoder_class::longPress() {
	bool tmp = this->longPres;
	this->longPres = false;
	return tmp;
}

bool Encoder_class::rotate() {
	bool tmp = this->rotation;
	this->rotation = false;
	return tmp;
}

int Encoder_class::getPosition() {
	int tmp = this->position;
	this->position = 0;
	return tmp;
}
Encoder_class Encoder = Encoder_class();
}
