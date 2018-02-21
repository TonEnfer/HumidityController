/*
 * EditInstHum.h
 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef EDITINSTHUM_H_
#define EDITINSTHUM_H_

#include <FSM/EndpointNode.h>

namespace FSM {

class EditInstalledHumidity: public EndpointNode {
public:
	void NodeEnterFunction(void);
	static EditInstalledHumidity& getInstance() {
		static EditInstalledHumidity eih;
		return eih;
	}
};

}
#endif /* EDITINSTHUM_H_ */
