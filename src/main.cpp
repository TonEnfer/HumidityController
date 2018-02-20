/*
 * main.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <main.h>

#include <FSM/FinalStateMashine.h>
#include <Settings.h>
#include <HAL/BME280.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>
#include <HAL/Encoder.h>

FSM::FinalStateMashine fsm;

int main() {
	SystemCoreClockUpdate();
	fsm = FSM::FinalStateMashine();
	//HAL::Display.init();
	HAL::Sensor.init();
	HAL::Encoder.init();
	HAL::Out.init();


	__enable_irq();

	while (true) {
		fsm.run();
		Settings::Parameters.setCurHumidity(HAL::Sensor.getHumidity());
		delay_us(100);
	}

	return 0;
}
