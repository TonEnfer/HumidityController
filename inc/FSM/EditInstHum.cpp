/*
 * EditInstHum.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditInstHum.h>
namespace FSM {
void EditInstalledHumidity::NodeEnterFunction(void) {
	uint8_t newHum = Parameters.normalize(
			Parameters.getMaxHumidity() + HAL::Encoder.getPosition());
	Parameters.setMaxHumidity(newHum);

}
}
