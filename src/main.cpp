/*
 * main.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <delay.h>
#include <FSM/FinalStateMashine.h>
#include <HAL/BME280.h>
#include <HAL/Encoder.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>
#include <main.h>
#include <sys/_stdint.h>
#include <system_stm32f0xx.h>
#include <Settings.h>

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
