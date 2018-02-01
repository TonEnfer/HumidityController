/*
 * encoder.cpp
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <HAL/Encoder.h>
namespace HAL {
Encoder::Encoder() {
	// TODO Auto-generated constructor stub

}

bool Encoder::press() {
	bool tmp = this->pres;
	this->pres = false;
	return tmp;
}

bool Encoder::longPress() {
	bool tmp = this->longPres;
	this->longPres = false;
	return tmp;
}

bool Encoder::rotate() {
	bool tmp = this->rotation;
	this->rotation = false;
	return tmp;
}

int Encoder::getPosition() {
	int tmp = this->position;
	this->position = 0;
	return tmp;
}
}
