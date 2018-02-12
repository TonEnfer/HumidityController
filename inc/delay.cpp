/*
 * delay.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <delay.h>

// SysTick interrupt handler
void SysTick_Handler() {
	if (TimingDelay != 0) { TimingDelay--; }
}

// Do delay for mSecs milliseconds
void delay_ms(uint32_t mSecs) {
	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_MS);
	TimingDelay = mSecs+1;
	while (TimingDelay != 0);
}

// Do delay for nSecs microseconds
void delay_us(uint32_t uSecs) {
	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_US);
	TimingDelay = uSecs+1;
	while (TimingDelay != 0);
}
