/*
 * EditInstTime.h
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef EDITCURRENTTIME_H_
#define EDITCURRENTTIME_H_

#include <FSM/EndpointNode.h>
namespace FSM {
class EditCurrentTime: public EndpointNode {

public:
	void NodeEnterFunction(void);
	static EditCurrentTime& getInstance() {
		static EditCurrentTime edct;
		return edct;
	}
};
}
#endif /* EDITCURRENTTIME_H_ */
