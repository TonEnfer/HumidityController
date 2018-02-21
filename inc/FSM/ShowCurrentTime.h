/*
 * ShowInstTime.h
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef SHOWCURRENTTIME_H_
#define SHOWCURRENTTIME_H_

#include <FSM/FsmNode.h>

namespace FSM {

class ShowCurrentTime: public FsmNode {
public:
	static ShowCurrentTime& getInstance() {
		static ShowCurrentTime t;
		return t;
	}
	void NodeEnterFunction(void);
	void NodeExitFunction(void);
	FsmNode& NodeSwitchFunction(void);
};

}
#endif /* SHOWCURRENTTIME_H_ */
