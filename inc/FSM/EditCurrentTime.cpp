/*
 * EditInstTime.cpp
 *
 *  Created on: 1 февр. 2018 г.
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
