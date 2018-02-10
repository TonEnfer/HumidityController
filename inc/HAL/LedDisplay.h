/*
 * LedDisplay.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_
#include <main.h>
namespace HAL {

class LedDisplay {
public:
	LedDisplay();
	void init();
	void show(uint8_t);
	void off();
};
extern LedDisplay Display;
}
#endif /* LEDDISPLAY_H_ */
