/*
 * LedDisplay.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include <sys/_stdint.h>

namespace HAL {

class LedDisplay {
protected:
	const uint16_t numArray[11] = { 0b10000011001110, //0
			0b10000000000010, //1
			0b10000001101100, //2
			0b10000001101010, //3
			0b10000010100010, //4
			0b00000011101010, //5
			0b00000011101110, //6
			0b10000001000010, //7
			0b10000011101110, //8
			0b10000011101010, //9
			0b0000000000000 //10

			};

public:
	LedDisplay();
	void init();
	void show(uint8_t);
	void off();
	volatile uint16_t numbers[2] = { 0, 0 };
	volatile uint8_t curNum = 0;
	volatile uint32_t clearmask = (uint32_t) 0b10000011101110 << 16;
};
extern LedDisplay Display;
}
#endif /* LEDDISPLAY_H_ */
