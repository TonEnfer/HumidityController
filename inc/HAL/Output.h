/*
 * Output.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <main.h>
#include <HAL/Drivers/GPIO.h>
#include <Settings.h>

namespace HAL {
class Output {

public:
	Output();
	void init();
	void on();
	void off();
	void autoSwitch();
};
extern Output Out;
}
#endif /* OUTPUT_H_ */
