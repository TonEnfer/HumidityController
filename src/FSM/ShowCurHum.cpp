/*
 * ShowHum.cpp
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditCurrentTime.h>
#include <FSM/EndpointNode.h>
#include <FSM/ShowCurHum.h>
#include <FSM/ShowCurrentTime.h>
#include <FSM/ShowInstHum.h>
#include <HAL/Encoder.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>
#include <Settings.h>

namespace FSM {

FsmNode& ShowCurrentHumidity::NodeSwitchFunction(void) {

	FsmNode& curTime = ShowCurrentTime::getInstance();
	EndpointNode& editTime = EditCurrentTime::getInstance();
	if (HAL::Encoder.isLongPressed())
		return (ShowInstalledHumidity::getInstance());
	else if (HAL::Encoder.isPressed())
		return (curTime);
	else if (HAL::Encoder.isRotated()) {
		editTime.setCallbackNode(&curTime);
		return editTime;
	}
	HAL::Display.show(Settings::Parameters.getCurHumidity());
	HAL::Out.autoSwitch();

	return *this;
}
}
