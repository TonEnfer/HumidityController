/*
 * FSM.cpp
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <FSM/FinalStateMashine.h>

namespace FSM {
FsmNode* switchNode(FsmNode* current, FsmNode* next) {
	if (current != NULL)
		current->NodeExitFunction();
	if (next != NULL)
		next->NodeEnterFunction();
	return next;
}
FinalStateMashine::FinalStateMashine() {
	//Init FSM node this
	showCurHum = new ShowCurrentHumidity(&showInstHum, &showCurTime,
			&editInstTime);
	showCurTime = new ShowCurrentTime(&showCurHum, &editInstTime);
	editInstTime = new EditCurrentTime();
	showInstHum = new ShowInstalledHumidity(&showCurHum, &editInstHum);
	editInstHum = new EditInstalledHumidity();
	current = showCurHum;
}

void FinalStateMashine::run(void) {
	FsmNode* newNode = current->NodeSwitchFunction();
	if (newNode != current && newNode != NULL) {
		current = switchNode(current, newNode);
	}
}

FsmNode* FinalStateMashine::getCurrentNode(void) {
//	return current;
	return NULL;
}
}
