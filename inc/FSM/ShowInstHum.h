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
	ShowInstalledHumidity(){}
	~ShowInstalledHumidity(){}

public:
//	static ShowInstalledHumidity& getInstance()
//	{
//		static ShowInstalledHumidity h;
//		return h;
//	}
	void NodeEnterFunction(void);
	void NodeExitFunction(void);
	FsmNode& NodeSwitchFunction(void);
};
}
#endif /* SHOWINSTHUM_H_ */
