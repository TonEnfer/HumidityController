/*
 * EditInstHum.cpp
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/EditInstHum.h>
#include <HAL/Encoder.h>
#include <sys/_stdint.h>
#include <Settings.h>
#include <stdlib.h>

using namespace Settings;
namespace FSM {
void EditInstalledHumidity::NodeEnterFunction(void) {
	int32_t pos = HAL::Encoder.getPosition();
	uint8_t newHum = 0;
	int8_t q;
	if (abs(pos) < 10) {
		if (pos < 0)
			q = -1;
		else
			q = 1;
	} else {
		if (pos > 0)
			q = -10;
		else
			q = 10;
	}
	newHum = Parameters.normalize(Parameters.getMaxHumidity() + q);
	Parameters.setMaxHumidity(newHum);

}
}
