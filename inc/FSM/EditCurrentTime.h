/*
 * EditInstTime.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef EDITCURRENTTIME_H_
#define EDITCURRENTTIME_H_

#include <main.h>
#include <FSM/EndpointNode.h>
#include <Settings.h>
#include <HAL/Encoder.h>

using namespace Settings;
namespace FSM {
class EditCurrentTime: public EndpointNode {
public:
	void NodeEnterFunction(void);
};
}
#endif /* EDITCURRENTTIME_H_ */
