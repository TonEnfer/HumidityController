/*
 * EditInstHum.h
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef EDITINSTHUM_H_
#define EDITINSTHUM_H_

#include <FSM/EndpointNode.h>
#include <Settings.h>
#include <HAL/Encoder.h>
namespace FSM {

class EditInstalledHumidity: public EndpointNode {
public:
	void NodeEnterFunction(void);
};

}
#endif /* EDITINSTHUM_H_ */
