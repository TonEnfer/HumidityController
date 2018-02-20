/*
 * FsmNode.cpp
 *
 *  Created on: 17 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FSM/FsmNode.h>

extern "C" void TIM16_IRQHandler() {
	if (TIM16->SR & TIM_SR_UIF)
		Settings::Parameters.decNodeShowTime();
	TIM16->SR &= ~0xFFFF;
}

namespace FSM {
void FsmNode::startTimer() {
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
	TIM16->DIER |= TIM_DIER_UIE;
	TIM16->PSC = (uint16_t) (SystemCoreClock/1500); //1500 Hz
	TIM16->ARR = (uint16_t) 1500; //3 s
	TIM16->CNT = (uint16_t) 0; //Reset count val
	TIM16->EGR |= TIM_EGR_UG; //UPDATE auto-reload value;
	TIM16->CR1 |= TIM_CR1_URS | TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM16->SR &= ~0xFFFF;
	NVIC_SetPriority(TIM16_IRQn, 1);
	NVIC_EnableIRQ(TIM16_IRQn);
}

void FsmNode::stopTimer() {
	TIM16->CR1 &= ~TIM_CR1_CEN;
	TIM16->SR &= ~0xFFFF;
	TIM16->CNT = (uint16_t) 0;
}

void FsmNode::startCountingShowTime() {
	startTimer();
}
void FsmNode::stopCountingShowTime() {
	stopTimer();
}

}
