/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/ShowInstHum.h>
namespace FSM {
void ShowInstalledHumidity::NodeEnterFunction(void) {
	Settings::Parameters.setNodeShowTime(5);
	startCountingShowTime();
}

void ShowInstalledHumidity::NodeExitFunction(void) {
}

FsmNode& ShowInstalledHumidity::NodeSwitchFunction(void) {
	FsmNode& editInstallHum = EditInstalledHumidity::getInstance();
	if (Settings::Parameters.getNodeShowTime() == 0) {
		stopCountingShowTime();
		return ShowCurrentHumidity::getInstance();
	} else if (HAL::Encoder.isRotated()) {
		editInstallHum.setCallbackNode(this);
		return editInstallHum;
	} else {
		HAL::Display.count(Settings::Parameters.getMaxHumidity());
	}
	return *this;
}

}
