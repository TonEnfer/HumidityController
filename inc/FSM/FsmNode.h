/*
 * FsmNode.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef FSMNODE_H_
#define FSMNODE_H_

#include <main.h>

namespace FSM {

class FsmNode {
protected:
	FsmNode() {
	}
	virtual ~FsmNode() {
	}
public:
	virtual void NodeEnterFunction(void) {
	}
	;
	virtual void NodeExitFunction(void) {
	}
	;
	virtual FsmNode& NodeSwitchFunction(void);
	virtual void setCallbackNode(FsmNode *cb) {
	}
};

}
#endif /* FSMNODE_H_ */
