/*
 * EditInstHum.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef EDITINSTHUM_H_
#define EDITINSTHUM_H_

#include <main.h>
#include <FSM/EndpointNode.h>
#include <Settings.h>
#include <HAL/Encoder.h>

using namespace Settings;
namespace FSM {

class EditInstalledHumidity: public EndpointNode {
public:
	void NodeEnterFunction(void);
};

}
#endif /* EDITINSTHUM_H_ */
