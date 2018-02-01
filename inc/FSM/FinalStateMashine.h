/*
 * FSM.h
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef FINALSTATEMASHINE_H_
#define FINALSTATEMASHINE_H_
#include <FSM/ShowCurHum.h>
#include <FSM/ShowInstHum.h>
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
	FsmNode* getNode(void);
};
}
#endif /* FINALSTATEMASHINE_H_ */
