/*
 * ShowInstTime.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef SHOWCURRENTTIME_H_
#define SHOWCURRENTTIME_H_

#include <main.h>
#include <FSM/FsmNode.h>
#include <HAL/Encoder.h>
#include <Settings.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>

namespace FSM {

class ShowCurrentTime: public FsmNode {
private:
	ShowCurrentTime(){}
	~ShowCurrentTime(){}
public:
//	static ShowCurrentTime& getInstance(){
//		static ShowCurrentTime t;
//		return t;
//	}
	void NodeEnterFunction(void);
	void NodeExitFunction(void);
	FsmNode& NodeSwitchFunction(void);
};

}
#endif /* SHOWCURRENTTIME_H_ */
