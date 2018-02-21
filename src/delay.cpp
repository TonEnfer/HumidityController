/*
 * delay.cpp
 *
 *  Created on: 12 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <stm32f0xx.h>
#include <delay.h>

static volatile uint32_t TimingDelay; // __IO -- volatile

// SysTick interrupt handler
void SysTick_Handler() {
//	volatile uint32_t  a = SysTick->CTRL;
	if (TimingDelay != 0) {
		TimingDelay--;
	}
}

// Do delay for mSecs milliseconds
void delay_ms(uint32_t mSecs) {
	bool status = (SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_MS)
			!= 0UL);
	if (status)
		return;
	TimingDelay = mSecs + 1;
	while ((int32_t) TimingDelay != 0)
		;
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

// Do delay for nSecs microseconds
void delay_us(uint32_t uSecs) {
	bool status = (SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_US)
			!= 0UL);
	if (status)
		return;
	TimingDelay = uSecs + 1;
	while (TimingDelay != 0)
		;
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}
