/*
 * FSM.h
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef FINALSTATEMASHINE_H_
#define FINALSTATEMASHINE_H_

#include <FSM/FsmNode.h>

namespace FSM {

class FinalStateMashine {
private:
	FsmNode* current;
public:
	FinalStateMashine();
	void run(void);
	FsmNode* getCurrentNode(void);
};
}
#endif /* FINALSTATEMASHINE_H_ */
