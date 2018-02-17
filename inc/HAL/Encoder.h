/*
 * encoder.h
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <main.h>
#include <delay.h>

namespace HAL {
class Encoder_class {
public:
	Encoder_class();
	void init();
	bool isPressed();
	bool isLongPressed();
	bool isRotate();
	int getPosition();

	bool pres = false;
	bool longPres = false;
	bool rotation = false;
	int32_t position = 0;

private:

//protected:

};
extern Encoder_class Encoder;
}
#endif /* ENCODER_H_ */
