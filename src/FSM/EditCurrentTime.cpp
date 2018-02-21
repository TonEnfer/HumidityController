/*
 * EditInstTime.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditCurrentTime.h>
#include <HAL/Encoder.h>
#include <sys/_stdint.h>
#include <Settings.h>

using namespace Settings;

namespace FSM {
void EditCurrentTime::NodeEnterFunction(void) {
	uint32_t newTime = (Parameters.getNodeShowTime() / 60
			+ HAL::Encoder.getPosition()) * 60;
	Parameters.setInstTime(newTime);
}

}
