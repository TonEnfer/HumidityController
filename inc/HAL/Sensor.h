/*
 * Sensor.h
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */
#ifndef SENSOR_H_
#define SENSOR_H_

#include <sys/_stdint.h>

namespace HAL {

class Sensor_class {
public:
	virtual void init();
	virtual uint16_t getHumidity();
	virtual uint16_t getTemperature();
};
//extern Sensor_class* Sensor;
} /* namespace HAL */

#endif /* SENSOR_H_ */
