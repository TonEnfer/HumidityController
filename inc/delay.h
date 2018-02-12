/*
 * delay.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef DELAY_H_
#define DELAY_H_
#include <main.h>

#define DELAY_TICK_FREQUENCY_US 1000000   /* = 1MHZ -> microseconds delay */
#define DELAY_TICK_FREQUENCY_MS 1000      /* = 1kHZ -> milliseconds delay */

static __IO uint32_t TimingDelay; // __IO -- volatile
extern void delay_ms(uint32_t nTime);
extern void delay_us(uint32_t nTime);

#endif /* DELAY_H_ */
