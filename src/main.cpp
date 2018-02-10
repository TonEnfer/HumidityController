/*
 * main.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <main.h>

#include <FSM/FinalStateMashine.h>
#include <Settings.h>
FSM::FinalStateMashine fsm;
volatile uint8_t a = 0;
int main() {
	fsm = FSM::FinalStateMashine();
	Settings::Parameters.setCurHumidity(10);
	Settings::Parameters.setCurTime(6666);

	while (true) {
		a++;
	}
	return 0;
}

