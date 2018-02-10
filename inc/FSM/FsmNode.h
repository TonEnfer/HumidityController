/*
 * FsmNode.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef FSMNODE_H_
#define FSMNODE_H_

#include <main.h>

namespace FSM {

class FsmNode {
public:
	virtual void NodeEnterFunction(void){}
	virtual void NodeExitFunction(void){}
	virtual FsmNode* NodeSwitchFunction(void){return NULL;}
	virtual void setCallbackNode(FsmNode *cb){}
	virtual ~FsmNode(){}

};

}
#endif /* FSMNODE_H_ */
