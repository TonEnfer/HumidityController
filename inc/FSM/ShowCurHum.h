/*
 * ShowHum.h
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef SHOWCURHUM_H_
#define SHOWCURHUM_H_

#include <FSM/FsmNode.h>

namespace FSM {
class ShowCurrentHumidity: public FsmNode {
public:
	static ShowCurrentHumidity& getInstance() {
		static ShowCurrentHumidity me;
		return me;
	}
	FsmNode& NodeSwitchFunction(void);
};
}
#endif /* SHOWCURHUM_H_ */
