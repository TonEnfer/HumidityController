/*
 * BME280.cpp
 *
 *  Created on: 30 янв. 2018 г.
 *      Author: anton.samoylov
 */
// TODO Реализовать методы
#include <HAL/BME280.h>

namespace HAL {

BME280::BME280() {

}
void BME280::init(){}

int32_t BME280::getHumidity() {

	return 0;
}
int32_t BME280::getTemperature()
{
	return 0;
}
#ifdef USE_BME280
	Sensor_class *Sensor = new BME280();
#endif

}
