/*
 * main.cpp
 *
 *  Created on: 10 ����. 2018 �.
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
	fsm = FSM::FinalStateMashine();

	HAL::Display.init();
	HAL::Encoder.init();
	HAL::Out.init();
	HAL::Sensor.init();

	__enable_irq();

	while (true) {
		fsm.run();
		delay_us(100);
	}

	return 0;
}
