/*
 * ShowHum.cpp
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <FSM/EditCurrentTime.h>
#include <FSM/EndpointNode.h>
#include <FSM/ShowCurHum.h>
#include <FSM/ShowCurrentTime.h>
#include <FSM/ShowInstHum.h>

namespace FSM {
void ShowCurrentHumidity::NodeEnterFunction() {

}

FsmNode& ShowCurrentHumidity::NodeSwitchFunction(void) {
//
//	FsmNode& curTime = ShowCurrentTime::getInstance();
//	EndpointNode&  editTime  =EditCurrentTime::getInstance();
//	if (HAL::Encoder.isLongPressed())
//		return (ShowInstalledHumidity::getInstance());
//	else if (HAL::Encoder.isPressed())
//		return (curTime);
//	else if (HAL::Encoder.isRotate()) {
//		editTime.setCallbackNode(&curTime);
//		return editTime;
//	}
//	HAL::Display.show(Settings::Parameters.getCurHumidity());
//	HAL::Out.autoSwitch();

	return *this;
}

void ShowCurrentHumidity::NodeExitFunction(void) {

}
}
