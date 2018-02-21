/*
 * LedDisplay.cpp
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/LedDisplay.h>
#include <stm32f0xx.h>
#include <system_stm32f0xx.h>

volatile static uint8_t currentNumber;
extern "C" void TIM3_IRQHandler() {
	;
	uint16_t num = HAL::Display.numbers[currentNumber];
	if (currentNumber == 0) {
		GPIOA->BSRR = GPIO_BSRR_BR_14;
		GPIOA->BSRR = HAL::Display.clearmask;
		GPIOA->BSRR = num;
		GPIOA->BSRR = GPIO_BSRR_BS_4;
		currentNumber++;
	} else {
		GPIOA->BSRR = GPIO_BSRR_BR_4;
		GPIOA->BSRR = HAL::Display.clearmask;
		GPIOA->BSRR = num;
		GPIOA->BSRR = GPIO_BSRR_BS_14;
		currentNumber = 0;
	}
	TIM3->SR &= ~0xFFFF;
}

namespace HAL {
LedDisplay::LedDisplay() {

}

void LedDisplay::init() {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR13 | GPIO_PUPDR_PUPDR14);

	GPIOA->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
			| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0
			| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER13_0
			| GPIO_MODER_MODER14_0);
	GPIOA->OSPEEDR |= ( GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2
			| GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4
			| GPIO_OSPEEDER_OSPEEDR5 | GPIO_OSPEEDER_OSPEEDR6
			| GPIO_OSPEEDER_OSPEEDR7 | GPIO_OSPEEDR_OSPEEDR13
			| GPIO_OSPEEDR_OSPEEDR14);

	GPIOA->BSRR = clearmask;

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->PSC = (uint16_t) (SystemCoreClock / 6000000); //6MHz
	TIM3->ARR = (uint16_t) 0x4F00; // ~11ms
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CEN;

	NVIC_SetPriority(TIM3_IRQn, 3);
	NVIC_EnableIRQ(TIM3_IRQn);

}

void LedDisplay::show(uint8_t number) {
	if (number >= 99) {
		numbers[0] = numArray[9];
		numbers[1] = numArray[9];
	} else if (number >= 10) {
		numbers[0] = numArray[number % 10];
		numbers[1] = numArray[number / 10];
	} else {
		numbers[0] = numArray[number % 10];
		numbers[1] = numArray[10]; //Clear char
	}
}

void LedDisplay::off() {
	this->show(100);
}
LedDisplay Display = LedDisplay();
}
