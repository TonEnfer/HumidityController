/*
 * FsmNode.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef FSMNODE_H_
#define FSMNODE_H_

#include <main.h>
#include <Settings.h>

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
	void startCountingShowTime();
	void stopCountingShowTime();
protected:
	void startTimer();
	void stopTimer();
};

}
#endif /* FSMNODE_H_ */
