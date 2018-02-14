/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <FSM/ShowInstHum.h>
namespace FSM {
void ShowInstalledHumidity::NodeEnterFunction(void) {
}

void ShowInstalledHumidity::NodeExitFunction(void) {
}

FsmNode& ShowInstalledHumidity::NodeSwitchFunction(void) {
//TODO: Ёту херню нужно в течение 5 секунд показывать
	FsmNode& editInstallHum = EditInstalledHumidity::getInstance();
	//FsmNode& me = ShowInstalledHumidity::getInstance();
	if (Settings::Parameters.getCurTime() == 0)
		return ShowCurrentHumidity::getInstance();
	else if (HAL::Encoder.isRotate()) {
		editInstallHum.setCallbackNode(this);
		return editInstallHum;
	}
	return *this;
}

}
