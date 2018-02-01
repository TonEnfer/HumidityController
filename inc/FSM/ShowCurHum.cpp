/*
 * ShowHum.cpp
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <FSM/ShowCurHum.h>

ShowCurrentHumidity::ShowCurrentHumidity(FsmNode** showInstallHum,
		FsmNode** showCurrentTime, FsmNode** editInstallTime) {
	this->showCurrentTime = showCurrentTime;
	this->showInstallHum = showInstallHum;
	this->editInstallTime = editInstallTime;
}

void ShowCurrentHumidity::NodeEnterFunction() {

}
FsmNode* ShowCurrentHumidity::NodeSwitchFunction(void) {
	return this;
}
void ShowCurrentHumidity::NodeExitFunction(void) {

}
