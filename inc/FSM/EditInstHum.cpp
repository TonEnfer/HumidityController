/*
 * EditInstHum.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <FSM/EditInstHum.h>
namespace FSM {
void EditInstalledHumidity::NodeEnterFunction(void) {
	if (HAL::Encoder.isRotate()) {
		Settings::maximumHumidity = Settings::normalize(
				Settings::maximumHumidity + HAL::Encoder.getPosition());
	}
}
}
