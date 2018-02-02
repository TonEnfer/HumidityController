/*
 * Settings.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_
#include "stm32f0xx.h"

//#include <sys/_stdint.h>
namespace Settings {
volatile static char maximumHumidity = 50;
volatile static char currentHumidity = 0;
volatile static char installedTime = 5;
volatile static char currentTime = 0;
}
;

#endif /* SETTINGS_H_ */
