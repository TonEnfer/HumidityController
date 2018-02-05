/*
 * encoder.cpp
 *
 *  Created on: 30 янв. 2018 г.
 *      Author: anton.samoylov
 */
// TODO Проверить методы
#include <HAL/Encoder.h>
namespace HAL {
Encoder_class::Encoder_class() {


}

bool Encoder_class::isPressed() {
	bool tmp = this->pres;
	this->pres = false;
	return tmp;
}

bool Encoder_class::isLongPressed() {
	bool tmp = this->longPres;
	this->longPres = false;
	return tmp;
}

bool Encoder_class::isRotate() {
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
