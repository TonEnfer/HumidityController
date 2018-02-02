/*
 * Sensor.h
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */
#include "stm32f0xx.h"
#include <FixNew.h>
#ifndef SENSOR_H_
#define SENSOR_H_

namespace HAL {


class Sensor_class {
public:
	//Sensor_class();
	virtual void init() = 0;
	virtual uint8_t getHumidity() = 0;
	virtual ~Sensor_class(){};
private:

};
extern Sensor_class* Sensor;
} /* namespace HAL */

#endif /* SENSOR_H_ */
