/*
 * FSM.cpp
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/FinalStateMashine.h>
#include <FSM/ShowCurHum.h>

namespace FSM {
FsmNode* switchNode(FsmNode* current, FsmNode* next) {
	if (current != nullptr)
		current->NodeExitFunction();
	if (next != nullptr)
		next->NodeEnterFunction();
	return next;
}
FinalStateMashine::FinalStateMashine() {
	current = &ShowCurrentHumidity::getInstance();
}

void FinalStateMashine::run(void) {
	FsmNode& newNode = current->NodeSwitchFunction();
	if (&newNode != current) {
		current = switchNode(current, &newNode);
	}
}

FsmNode* FinalStateMashine::getCurrentNode(void) {
	return current;
//	return NULL;
}
}
