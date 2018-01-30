/*
 * FsmNode.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef FSMNODE_H_
#define FSMNODE_H_
#include "stddef.h"
class FsmNode {
public:
	void (*NodeEnterFunction)(void) = NULL;
	void (*NodeExitFunction)(void) = NULL;
	void (*NodeSwitchFunction)(void) = NULL;
	static FsmNode* switchNode(FsmNode* current, FsmNode* next);
};

#endif /* FSMNODE_H_ */
