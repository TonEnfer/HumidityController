/*
 * FsmNode.cpp
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <FSM/FsmNode.h>

static FsmNode* switchNode(FsmNode* current, FsmNode* next) {
	if (current->NodeExitFunction != NULL) {
		current->NodeExitFunction();
	}
	if (next->NodeEnterFunction != NULL) {
		next->NodeEnterFunction();
	}
	return next;
}

