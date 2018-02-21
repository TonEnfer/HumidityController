/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditInstHum.h>
#include <FSM/ShowCurHum.h>
#include <FSM/ShowInstHum.h>
#include <HAL/Encoder.h>
#include <HAL/LedDisplay.h>
#include <Settings.h>

namespace FSM {
void ShowInstalledHumidity::NodeEnterFunction(void) {
	Settings::Parameters.setNodeShowTime(5);
	startCountingShowTime();
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
		HAL::Display.show(Settings::Parameters.getMaxHumidity());
	}
	return *this;
}

}
