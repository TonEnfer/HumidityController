/*
 * Sensor.h
 *
 *  Created on: 2 февр. 2018 г.
 *      Author: anton.samoylov
 */
#ifndef SENSOR_H_
#define SENSOR_H_

#include <main.h>

namespace HAL {

class Sensor_class {
public:
	//Sensor_class();
	virtual void init();
	virtual uint16_t getHumidity();
	virtual uint16_t getTemperature();
	virtual ~Sensor_class(){};
private:

};
//extern Sensor_class* Sensor;
} /* namespace HAL */

#endif /* SENSOR_H_ */
