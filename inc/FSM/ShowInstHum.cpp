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
//	if (Settings::Parameters.getCurTime() == 0)
//		return (**showCurrentHum);
//	else if (HAL::Encoder.isRotate()) {
//		if (editInstallHum != NULL && (*editInstallHum) != NULL) {
//			(*editInstallHum)->setCallbackNode(this);
//			//(*(*editInstallHum)).setCallbackNode(this);
//			return (**editInstallHum);
//		}
//	}
	return *this;
}

}
