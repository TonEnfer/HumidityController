/*
 * Settings.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <Settings.h>

namespace Settings {
char normalize(char value) {
	if (value > 100)
		return 99;
	else
		return value;
}
}

