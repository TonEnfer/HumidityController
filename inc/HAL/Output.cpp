/*
 * Output.cpp
 *
 *  Created on: 30 янв. 2018 г.
 *      Author: anton.samoylov
 */
// TODO Реализовать методы
#include <HAL/Output.h>
namespace HAL {
Output::Output() {


}

void Output::on() {

}
void Output::off() {

}

void Output::autoSwitch() {
	if (Settings::currentHumidity > Settings::maximumHumidity)
		this->on();
	else
		this->off();
}
Output Out = Output();
}
