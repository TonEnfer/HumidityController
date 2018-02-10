/*
 * EndPointNode.h
 *
 *  Created on: 5 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef ENDPOINTNODE_H_
#define ENDPOINTNODE_H_

#include <main.h>
#include <FSM/FsmNode.h>

namespace FSM {

class EndpointNode: public FsmNode {
protected:
	FsmNode *callbackNode = NULL;
public:
	FsmNode* NodeSwitchFunction(void) {
		if (callbackNode != NULL)
			return callbackNode;
		else
			return this;
	}
	void setCallbackNode(FsmNode *cb) {
		callbackNode = cb;
	}

};

} /* namespace FSM */

#endif /* ENDPOINTNODE_H_ */
