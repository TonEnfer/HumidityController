/*
 * Output.cpp
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */
// TODO ����������� ������
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
