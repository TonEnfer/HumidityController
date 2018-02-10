/*
 * ShowInstTime.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <FSM/ShowCurrentTime.h>
namespace FSM {
ShowCurrentTime::ShowCurrentTime(FsmNode** ShowCurHum, FsmNode** EditCurTime) {
	this->ShowCurHum = ShowCurHum;
	this->EditCurTime = EditCurTime;
}
void ShowCurrentTime::NodeEnterFunction(void) {

}
void ShowCurrentTime::NodeExitFunction(void) {
	if (Settings::Parameters.getCurHumidity()
			<= Settings::Parameters.getMaxHumidity())
		HAL::Out.off();
}
FsmNode* ShowCurrentTime::NodeSwitchFunction(void) {
	if (HAL::Encoder.isRotate())
		if (EditCurTime != NULL && (*EditCurTime) != NULL) {
			(*EditCurTime)->setCallbackNode(this);
			return (*EditCurTime);
		}

	if (Settings::Parameters.getCurTime() != 0) {
		HAL::Display.show(Settings::Parameters.getCurTime());
		HAL::Out.on();
	} else
		return (*ShowCurHum);

	return this;
}
}
