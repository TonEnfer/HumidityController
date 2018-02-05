/*
 * FsmNode.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef FSMNODE_H_
#define FSMNODE_H_
#include "stddef.h"
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
