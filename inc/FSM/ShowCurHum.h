/*
 * ShowHum.h
 *
 *  Created on: 31 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef SHOWCURHUM_H_
#define SHOWCURHUM_H_

#include <FSM/FsmNode.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>
#include <HAL/Encoder.h>
#include <Settings.h>
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
