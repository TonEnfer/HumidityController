/*
 * BME280.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef BME280_H_
#define BME280_H_

#include <main.h>
#include <HAL/Sensor.h>

namespace HAL {
class BME280: public Sensor_class {
public:
	BME280();
	void init();
	int32_t getHumidity();
int32_t getTemperature();
	~BME280(){};
};
}
#endif /* BME280_H_ */
