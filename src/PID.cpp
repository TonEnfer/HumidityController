/*
 * PID.cpp
 *
 *  Created on: 22 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <PID.h>

extern "C" void TIM17_IRQHandler() {
//	uint32_t outVal = Regulator.compute(Settings::Parameters.getCurHumidity());
//	Regulator.setValue(outVal);
}

PID::PID(uint32_t Kp, uint32_t Ki, uint32_t Kd) {
	this->Kp = Kp;
	this->Kd = Kd;
	this->Ki = Ki;
}

void PID::init() {
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	TIM17->DIER |= TIM_DIER_UIE;
	TIM17->PSC = (uint16_t) (SystemCoreClock / 10000) - 1; //10 kHz
	TIM17->ARR = (uint16_t) 10000; //1 s
	TIM17->CNT = (uint16_t) 0; //Reset count val
	TIM17->EGR |= TIM_EGR_UG; //UPDATE auto-reload value;
	TIM17->CR1 |= TIM_CR1_URS | TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM17->SR &= ~0xFFFF;
	NVIC_SetPriority(TIM17_IRQn, 2);
	NVIC_EnableIRQ(TIM17_IRQn);
	//TODO init timer
}
uint32_t PID::getValue() {
	return this->outValue;
}

void PID::setValue(uint32_t outValue) {
	this->outValue = outValue;
}
const float filterK = 0.5;
uint32_t PID::compute(uint32_t inputValue) {
	int32_t error = Settings::Parameters.getMaxHumidity() - inputValue;
	static uint32_t oldError;
	static uint32_t oldI, oldD;
	int32_t P = error;
	int32_t I = oldI + error;
	int32_t D = error - oldError;
	D = (int32_t) ((1.0 - filterK) * oldD + filterK * D);
	oldError = error;
	oldI = I;
	oldD = D;
	return Kp * P + Ki * I + Kd * D;
}
