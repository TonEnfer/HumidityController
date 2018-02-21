/*
 * FsmNode.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef FSMNODE_H_
#define FSMNODE_H_

namespace FSM {

class FsmNode {
public:
	virtual void NodeEnterFunction(void) {
	}

	virtual void NodeExitFunction(void) {
	}

	virtual FsmNode& NodeSwitchFunction(void)=0;
	virtual void setCallbackNode(FsmNode *cb) {
		(void) cb;
	}
	void startCountingShowTime();
	void stopCountingShowTime();
protected:
	void startTimer();
	void stopTimer();
};

}
#endif /* FSMNODE_H_ */
