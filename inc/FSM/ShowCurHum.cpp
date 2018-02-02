/*
 * ShowHum.cpp
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <FSM/ShowCurHum.h>
namespace FSM {
ShowCurrentHumidity::ShowCurrentHumidity(FsmNode** showInstallHum,
		FsmNode** showCurrentTime, FsmNode** editInstallTime) {
	this->showCurrentTime = showCurrentTime;
	this->showInstallHum = showInstallHum;
	this->editInstallTime = editInstallTime;
}

void ShowCurrentHumidity::NodeEnterFunction() {

}


FsmNode* ShowCurrentHumidity::NodeSwitchFunction(void) {

	HAL::Display.show(Settings::currentHumidity);
	HAL::Out.autoSwitch();

	return this;
}

void ShowCurrentHumidity::NodeExitFunction(void) {

}
}
