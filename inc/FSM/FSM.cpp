/*
 * FSM.cpp
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <FSM/FSM.h>


FsmNode* switchNode(FsmNode* current, FsmNode* next) {
	if(current!=NULL)
		current->NodeExitFunction();
	if(next!=NULL)
		next->NodeEnterFunction();
	return next;
}
FsmNode inst = FsmNode();
FSM::FSM() {
	//Init FSM node this
	showCurHum = new ShowCurrentHumidity(&showInstHum,&showCurTime,&editInstTime);
	showCurTime = new FsmNode();
	editInstTime = new FsmNode();
	showInstHum = new FsmNode();;
	current = showCurHum;
}

void FSM::run(void){
	FsmNode* newNode = current->NodeSwitchFunction();
	if(newNode!=current && newNode!=NULL){
		current = switchNode(current, newNode);
	}
}

FsmNode* FSM::getNode(void){
//	return current;
	return NULL;
}
