/*
 * BME280.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef BME280_H_
#define BME280_H_

#include "stm32f0xx.h"
#include <HAL/Sensor.h>

namespace HAL {
class BME280: public Sensor_class {
public:
	BME280();
	void init();
	uint8_t getHumidity();
	~BME280(){};
};
}
#endif /* BME280_H_ */
