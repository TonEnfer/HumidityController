/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <FSM/ShowInstHum.h>
namespace FSM {
ShowInstalledHumidity::ShowInstalledHumidity(FsmNode** showCurrentHum,
		FsmNode** editInstallHum) {
	this->showCurrentHum = showCurrentHum;
	this->editInstallHum = editInstallHum;
}

void ShowInstalledHumidity::NodeEnterFunction(void) {
}

void ShowInstalledHumidity::NodeExitFunction(void) {
}

FsmNode* ShowInstalledHumidity::NodeSwitchFunction(void) {
//TODO: Ёту херню нужно в течение 5 секунд показывать
	if (Settings::currentTime == 0)
		return (*showCurrentHum);
	else if (HAL::Encoder.isRotate()) {
		if (editInstallHum != NULL && (*editInstallHum) != NULL) {
			(*editInstallHum)->setCallbackNode(this);
			//(*(*editInstallHum)).setCallbackNode(this);
			return (*editInstallHum);
		}
	}
	return this;
}

}
