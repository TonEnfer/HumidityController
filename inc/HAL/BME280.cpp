/*
 * BME280.cpp
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */
// TODO ����������� ������
#include <HAL/BME280.h>

namespace HAL {

BME280::BME280() {

}
void BME280::init(){}

uint8_t BME280::getHumidity() {

	return 0;
}
#ifdef USE_BME280
	Sensor_class *Sensor = new BME280();
#endif

}
