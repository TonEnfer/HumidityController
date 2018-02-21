/*
 * Output.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

namespace HAL {
class Output {

public:
	void init();
	void on();
	void off();
	void autoSwitch();
};
extern Output Out;
}
#endif /* OUTPUT_H_ */
