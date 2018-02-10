/*
 * Sensor.h
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */
#ifndef SENSOR_H_
#define SENSOR_H_

#include <main.h>

namespace HAL {

class Sensor_class {
public:
	//Sensor_class();
	virtual void init() = 0;
	virtual int32_t getHumidity() = 0;
	virtual int32_t getTemperature() = 0;
	virtual ~Sensor_class(){};
private:

};
extern Sensor_class* Sensor;
} /* namespace HAL */

#endif /* SENSOR_H_ */
