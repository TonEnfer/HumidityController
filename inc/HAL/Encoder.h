/*
 * encoder.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f0xx.h"
namespace HAL {
class Encoder_class {
public:
	Encoder_class();
	void init();
	bool press();
	bool longPress();
	bool rotate();
	int getPosition();

private:
	bool pres = false;
	bool longPres = false;
	bool rotation = false;
	int position = 0;
//protected:

};
extern Encoder_class Encoder;
}
#endif /* ENCODER_H_ */
