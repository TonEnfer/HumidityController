/*
 * EndPointNode.h
 *
 *  Created on: 5 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef ENDPOINTNODE_H_
#define ENDPOINTNODE_H_

#include <main.h>
#include <FSM/FsmNode.h>

namespace FSM {

class EndpointNode: public FsmNode {
//private:
//	EndpointNode();
protected:
	FsmNode *callbackNode = NULL;
public:
	FsmNode& NodeSwitchFunction(void) {
		if (callbackNode != NULL)
			return (*callbackNode);
		else
			return *this;
	}
	void setCallbackNode(FsmNode *cb) {
		callbackNode = cb;
	}
};

} /* namespace FSM */

#endif /* ENDPOINTNODE_H_ */
