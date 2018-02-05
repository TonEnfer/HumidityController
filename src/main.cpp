#include "stm32f030x6.h"
#include <stdlib.h>
#include <FixNew.h>

#include <HAL/Sensor.h>
#include <HAL/LedDisplay.h>
#include <HAL/Encoder.h>
#include <HAL/Output.h>

#include <FSM/FinalStateMashine.h>

#include <Settings.h>

FSM::FinalStateMashine fsm;

void init() {
	HAL::Sensor->init();
	volatile unsigned int ms = RTC_SSR_SS;
	//HAL::Encoder.init();
}

int main(void) {
	init();
	while (true) {
		fsm.run();
	}
}
