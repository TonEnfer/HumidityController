/*
 * ShowInstHum.h
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef SHOWINSTHUM_H_
#define SHOWINSTHUM_H_

#include <FSM/FsmNode.h>

namespace FSM {
class ShowInstalledHumidity: public FsmNode {
public:
	static ShowInstalledHumidity& getInstance() {
		static ShowInstalledHumidity h;
		return h;
	}
	void NodeEnterFunction(void);
	void NodeExitFunction(void);
	FsmNode& NodeSwitchFunction(void);
};
}
#endif /* SHOWINSTHUM_H_ */
