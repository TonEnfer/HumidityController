/*
 * DHT22.h
 *
 *  Created on: 2 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef DHT22_H_
#define DHT22_H_

#include <main.h>
#include <HAL/Sensor.h>

namespace HAL {

class DHT22: public Sensor_class {
public:
	DHT22();
	void init();
	int32_t getHumidity();
	int32_t getTemperature();
	~DHT22(){};
};

} /* namespace HAL */

#endif /* DHT22_H_ */
