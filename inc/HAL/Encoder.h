/*
 * encoder.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <sys/_stdint.h>

namespace HAL {
class Encoder_class {
public:
	Encoder_class();
	void init();
	bool isPressed();
	bool isLongPressed();
	bool isRotated();
	int getPosition();

	volatile bool pres = false;
	volatile bool longPres = false;
	volatile bool rotation = false;
	volatile int32_t position = 0;

private:

//protected:

};
extern Encoder_class Encoder;
}
#endif /* ENCODER_H_ */
