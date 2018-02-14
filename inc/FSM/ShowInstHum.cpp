/*
 * ShowInstHum.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/ShowInstHum.h>
namespace FSM {
void ShowInstalledHumidity::NodeEnterFunction(void) {
}

void ShowInstalledHumidity::NodeExitFunction(void) {
}

FsmNode& ShowInstalledHumidity::NodeSwitchFunction(void) {
//TODO: ��� ����� ����� � ������� 5 ������ ����������
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
