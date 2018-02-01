#include <stdlib.h>

#include "stm32f0xx.h"

#include <HAL/BME280.h>
#include <HAL/Encoder.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>

#include <FixNew.h>
#include <FSM/FinalStateMashine.h>





HAL::LedDisplay display;
HAL::BME280 sensor;
HAL::Output out;
HAL::Encoder enc;

FSM::FinalStateMashine fsm;

void init() {
	display.init();
}

int main(void) {


	init();
	while (true) {
		fsm.run();
	}
}
