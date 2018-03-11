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
//	HAL::Out.init();

	while (true) {
		volatile uint16_t temperature = HAL::Sensor.getTemperature();
		volatile uint16_t h = HAL::Sensor.getHumidity();
		HAL::Display.show((uint8_t) temperature);
		delay_ms(1000);
		HAL::Display.show((uint8_t)h);
		delay_ms(1000);



	}
	while (true) {
		fsm.run();
		HAL::Sensor.getTemperature();
		uint8_t H = HAL::Sensor.getHumidity();
		Settings::Parameters.setCurHumidity(H);
		delay_us(100);
	}
	return 0;
}
