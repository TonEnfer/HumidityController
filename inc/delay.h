/*
 * delay.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: anton.samoylov
 */
#pragma once
#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f0xx.h"
#include <stdint.h>

#define DELAY_TICK_FREQUENCY_US 1000000   /* = 1MHZ -> microseconds delay */
#define DELAY_TICK_FREQUENCY_MS 1000      /* = 1kHZ -> milliseconds delay */


void delay_ms(uint32_t nTime);
void delay_us(uint32_t nTime);

extern "C" void SysTick_Handler();

#endif /* DELAY_H_ */
