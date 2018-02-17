/*
 * ShowInstTime.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <FSM/ShowCurrentTime.h>
namespace FSM {
void ShowCurrentTime::NodeEnterFunction(void) {
	uint32_t ct = Settings::Parameters.getInsTime();
	Settings::Parameters.setNodeShowTime(ct);
	startCountingShowTime();
}
void ShowCurrentTime::NodeExitFunction(void) {
	stopCountingShowTime();
}
FsmNode& ShowCurrentTime::NodeSwitchFunction(void) {
	FsmNode& EditCurTime = EditCurrentTime::getInstance();
	if (HAL::Encoder.isRotate()) {
		EditCurTime.setCallbackNode(this);
		return EditCurTime;
	}
	if(HAL::Encoder.isPressed()){
		return ShowCurrentHumidity::getInstance();
	}
	uint8_t ct = (uint8_t)(Settings::Parameters.getNodeShowTime()/60);
	if (ct != 0) {
		HAL::Display.show(ct);
		HAL::Out.on();
	} else
		return ShowCurrentHumidity::getInstance();

	return *this;
}
}
