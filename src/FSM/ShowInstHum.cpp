/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 февр. 2018 г.
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
	} else if (HAL::Encoder.isRotate()) {
		editInstallHum.setCallbackNode(this);
		return editInstallHum;
	} else {
		HAL::Display.show(Settings::Parameters.getMaxHumidity());
	}
	return *this;
}

}
