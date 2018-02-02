/*
 * BME280.cpp
 *
 *  Created on: 30 янв. 2018 г.
 *      Author: anton.samoylov
 */

#include <HAL/BME280.h>

namespace HAL {

BME280::BME280() {
	// TODO BME280 Написать конструктор
}
void BME280::init(){}

uint8_t BME280::getHumidity() {
	// TODO BME280 Написать метод, возвращающий влажность
	return 0;
}
#ifdef USE_BME280
	Sensor_class *Sensor = new BME280();
#endif

}
