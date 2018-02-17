/*
 * EditInstTime.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditCurrentTime.h>
namespace FSM {
void EditCurrentTime::NodeEnterFunction(void) {
	uint32_t newTime = (Parameters.getNodeShowTime()/60
			+ HAL::Encoder.getPosition())*60;
	Parameters.setInstTime(newTime);
}

}
