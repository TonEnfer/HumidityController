/*
 * ShowInstHum.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef SHOWINSTHUM_H_
#define SHOWINSTHUM_H_

#include <main.h>
#include <FSM/FsmNode.h>
#include <HAL/Encoder.h>
#include <Settings.h>

namespace FSM {
class ShowInstalledHumidity: public FsmNode {
private:
	ShowInstalledHumidity();
	FsmNode** showCurrentHum;
	FsmNode** editInstallHum;
public:
	ShowInstalledHumidity(FsmNode** showCurrentHum,
			FsmNode** editInstallHum);
	void NodeEnterFunction(void);
	void NodeExitFunction(void);
	FsmNode* NodeSwitchFunction(void);
public:

};
}
#endif /* SHOWINSTHUM_H_ */
