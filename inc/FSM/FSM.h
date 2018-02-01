/*
 * FSM.h
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef FSM_H_
#define FSM_H_
#include <FSM/ShowCurHum.h>

class FSM {
private:
	FsmNode* showCurHum;
	FsmNode* showCurTime;
	FsmNode* editInstTime;
	FsmNode* showInstHum;

	FsmNode* current;
public:
	FSM();
	void run(void);
	FsmNode* getNode(void);
};

#endif /* FSM_H_ */
