/*
 * DHT22.cpp
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/DHT22.h>
// TODO ����������� ������
namespace HAL {

DHT22::DHT22() {

}
void DHT22::init() {
}
uint8_t DHT22::getHumidity() {
 return 0;
}

#ifdef USE_DHT22
Sensor_class *Sensor = new DHT22();
#endif

}
/* namespace HAL */
