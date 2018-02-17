/*
 * LedDisplay.cpp
 *
 *  Created on: 30 џэт. 2018 у.
 *      Author: anton.samoylov
 */

#include <HAL/LedDisplay.h>

extern "C" void TIM3_IRQHandler() {
	TIM3->SR &= ~0xFFFF;
	uint16_t num = 	HAL::Display.numbers[0];
	GPIOA->BSRR = HAL::Display.clearmask;
	GPIOA->BSRR = num;
	GPIOA->BSRR = GPIO_BSRR_BS_4;
}

namespace HAL {
LedDisplay::LedDisplay() {

}

void LedDisplay::init() {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
			| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0
			| GPIO_MODER_MODER7_0 | GPIO_MODER_MODER4_0);
	GPIOA->OSPEEDR |= ( GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2
			| GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR5 |
			GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7
			| GPIO_OSPEEDER_OSPEEDR4);

	GPIOA->BSRR = clearmask;

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->PSC = (uint16_t) 7; //6MHz
	TIM3->ARR = (uint16_t) 0xFFFF; // ~11ms
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CEN;

	NVIC_SetPriority(TIM3_IRQn, 1);
	NVIC_EnableIRQ(TIM3_IRQn);

}

void LedDisplay::show(uint8_t number) {
	if (number > 10) {
		numbers[0] = numArray[number%10];
	} else {
		numbers[0] = numArray[number];
	}
}

void LedDisplay::off() {
	this->show(100);
}
LedDisplay Display = LedDisplay();
}
