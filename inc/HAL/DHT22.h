/*
 * DHT22.h
 *
 *  Created on: 2 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef DHT22_H_
#define DHT22_H_

#include <HAL/Sensor.h>

namespace HAL {

class DHT22: public Sensor_class {
public:
	DHT22();
	void init();
	uint8_t getHumidity();
	~DHT22(){};
};

} /* namespace HAL */

#endif /* DHT22_H_ */
