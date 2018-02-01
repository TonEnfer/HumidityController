#include "stm32f0xx.h"

#include <HAL/BME280.h>
#include <HAL/Encoder.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>

#include <FSM/FSM.h>
#include <stdlib.h>
#include <FixNew.h>

LedDisplay display;
BME280 sensor;
Output out;
Encoder enc;

FSM fsm;

void init() {
	display.init();
}

int main(void) {


	init();
	while (true) {
		fsm.run();
	}
}
