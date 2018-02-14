/*
 * EditInstTime.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditCurrentTime.h>
namespace FSM {
void EditCurrentTime::NodeEnterFunction(void) {
	uint32_t newTime = Parameters.getInsTime() + HAL::Encoder.getPosition();
	Parameters.setInstTime(newTime);
	Parameters.setCurTime(newTime);
}
}
