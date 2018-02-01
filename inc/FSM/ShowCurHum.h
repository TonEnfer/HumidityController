/*
 * ShowHum.h
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef SHOWCURHUM_H_
#define SHOWCURHUM_H_

#include <FSM/FsmNode.h>
namespace FSM {
class ShowCurrentHumidity: public FsmNode {
private:
	ShowCurrentHumidity();
	FsmNode** showInstallHum;
	FsmNode** showCurrentTime;
	FsmNode** editInstallTime;
public:
	ShowCurrentHumidity(FsmNode** showInstallHum, FsmNode** showCurrentTime,
			FsmNode** editInstallTime);
	void NodeEnterFunction(void);
	void NodeExitFunction(void);
	FsmNode* NodeSwitchFunction(void);

};
}
#endif /* SHOWCURHUM_H_ */
