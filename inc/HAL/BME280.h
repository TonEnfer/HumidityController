/*
 * BME280.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef BME280_H_
#define BME280_H_

#include "stm32f0xx.h"

class BME280 {
public:
	BME280();
	uint8_t getHum();
};

#endif /* BME280_H_ */
