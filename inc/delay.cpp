/*
 * delay.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <delay.h>
static volatile uint32_t TimingDelay; // __IO -- volatile

// SysTick interrupt handler
void SysTick_Handler() {
	if (TimingDelay != 0) {
		TimingDelay--;
	}
}


// Do delay for mSecs milliseconds
void delay_ms(uint32_t mSecs) {

	NVIC_EnableIRQ(SysTick_IRQn);
	__enable_irq();
	if(SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_MS) != 0UL)
		return;
	TimingDelay = mSecs + 1;
	while ((int32_t)TimingDelay != 0)
		;
	//NVIC_DisableIRQ(SysTick_IRQn);

}

// Do delay for nSecs microseconds
void delay_us(uint32_t uSecs) {
	NVIC_EnableIRQ(SysTick_IRQn);
	__enable_irq();
	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_US);
	TimingDelay = uSecs + 1;
	while (TimingDelay != 0)
		;
}
