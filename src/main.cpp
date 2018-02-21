/*
 * main.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include "main.h"

FSM::FinalStateMashine fsm;

int main() {
	SystemCoreClockUpdate();
	fsm = FSM::FinalStateMashine();
	HAL::Display.init();
	HAL::Sensor.init();
	HAL::Encoder.init();
	HAL::Out.init();

	while (true) {
		volatile uint16_t temperature = HAL::Sensor.getTemperature();
		HAL::Display.show((uint8_t) temperature);
	}
	while (true) {
		fsm.run();
		Settings::Parameters.setCurHumidity(HAL::Sensor.getHumidity());
		delay_us(100);
	}
	return 0;
}
