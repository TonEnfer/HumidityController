/*
 * DHT22.cpp
 *
 *  Created on: 2 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <HAL/DHT22.h>
// TODO Реализовать методы
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
