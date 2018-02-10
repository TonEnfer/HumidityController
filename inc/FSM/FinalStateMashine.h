/*
 * FSM.h
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef FINALSTATEMASHINE_H_
#define FINALSTATEMASHINE_H_

#include <main.h>

#include <FSM/EditCurrentTime.h>
#include <FSM/ShowCurHum.h>
#include <FSM/ShowInstHum.h>
#include <FSM/EditInstHum.h>
#include <FSM/ShowCurrentTime.h>

namespace FSM {
class FinalStateMashine {
private:
	FsmNode* showCurHum;
	FsmNode* showCurTime;
	FsmNode* editInstTime;
	FsmNode* showInstHum;
	FsmNode* editInstHum;

	FsmNode* current;

public:
	FinalStateMashine();
	void run(void);
	FsmNode* getCurrentNode(void);
};
}
#endif /* FINALSTATEMASHINE_H_ */
