/*
 * EditInstTime.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditCurrentTime.h>
namespace FSM {
//EditCurrentTime::EditCurrentTime() {
//
//
//}
void EditCurrentTime::NodeEnterFunction(void) {
	Settings::currentTime = Settings::normalize(
			Settings::currentTime + HAL::Encoder.getPosition());
}
}
