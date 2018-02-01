/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <FSM/ShowInstHum.h>

ShowInstalledHumidity::ShowInstalledHumidity(FsmNode** showCurrentHum,
		FsmNode** editInstallHum) {
	this->showCurrentHum = showCurrentHum;
	this->editInstallHum = editInstallHum;
}

void ShowInstalledHumidity::NodeEnterFunction(void){};
void ShowInstalledHumidity::NodeExitFunction(void){};
FsmNode* ShowInstalledHumidity::NodeSwitchFunction(void) {
	return NULL;
}

