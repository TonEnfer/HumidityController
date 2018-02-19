/*
 * encoder.cpp
 *
 *  Created on: 30 янв. 2018 г.
 *      Author: anton.samoylov
 */
// TODO Проверить методы
#include <HAL/Encoder.h>

extern "C" void EXTI0_1_IRQHandler() {
	static uint8_t oldA, oldB;
	volatile uint8_t A = HAL::GPIO::readInputDataBit(GPIOF, GPIO_IDR_0);
	volatile uint8_t B = HAL::GPIO::readInputDataBit(GPIOF, GPIO_IDR_1);
	if (oldA ^ oldB ^ A ^ B) {
		if (oldA ^ B)
			HAL::Encoder.position++;
		else
			HAL::Encoder.position--;
	}
	oldA = A;
	oldB = B;
	EXTI->PR |= EXTI_PR_PR0 | EXTI_PR_PR1;
}

volatile static uint8_t sw_pr_time;

#define BUTTON_PRESSED 0
extern "C" void TIM14_IRQHandler() {
	volatile static uint8_t old_state;
	uint8_t sw_state = HAL::GPIO::readInputDataBit(GPIOA, GPIO_IDR_0);
	if (sw_state != BUTTON_PRESSED) {
		if (old_state != BUTTON_PRESSED)
			sw_pr_time++;
		else
			sw_pr_time = 0;
	} else {
		if (old_state != BUTTON_PRESSED) {
			if (sw_pr_time < 50) {
				HAL::Encoder.pres = true;
			} else {
				HAL::Encoder.pres = false;
				HAL::Encoder.longPres = true;
			}
		}
	}
	old_state = sw_state;
	TIM14->SR &= ~0xFFFF;

}

namespace HAL {
Encoder_class::Encoder_class() {

}

void Encoder_class::init() {
//Config ENC_A and ENC_B pins
//Enable clock
	RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

//Pin config
	GPIOF->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);	//Input
	GPIOF->PUPDR |= (GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0);	//Pull-up

//Conf ENC_SW pin
//en clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//pin config
	GPIOA->MODER &= ~GPIO_MODER_MODER0; //input
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR0_0); //Pull-up

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PF | SYSCFG_EXTICR1_EXTI1_PF;

	EXTI->FTSR |= EXTI_FTSR_TR0 | EXTI_FTSR_TR1;
	EXTI->RTSR |= EXTI_RTSR_TR0 | EXTI_RTSR_TR1;

	NVIC_SetPriority(EXTI0_1_IRQn, 1);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR1;

	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->DIER |= TIM_DIER_UIE;
	TIM14->PSC = (uint16_t) 127; //375 kHz
	TIM14->ARR = (uint16_t) 37499; //100 ms
	TIM14->CNT = (uint16_t) 0; //Reset count val
	TIM14->EGR |= TIM_EGR_UG; //UPDATE auto-reload value;
	TIM14->CR1 |= TIM_CR1_URS | TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM14->SR &= ~0xFFFF;
	NVIC_SetPriority(TIM14_IRQn, 1);
	NVIC_EnableIRQ(TIM14_IRQn);
//TIM14->CR1 |= TIM_CR1_CEN;
}

bool Encoder_class::isPressed() {
	bool tmp = this->pres;
	this->pres = false;
	return tmp;
}

bool Encoder_class::isLongPressed() {
	bool tmp = this->longPres;
	this->longPres = false;
	return tmp;
}

bool Encoder_class::isRotate() {
	bool tmp = this->rotation;
	this->rotation = false;
	return tmp;
}

int Encoder_class::getPosition() {
	int tmp = this->position;
	this->position = 0;
	return tmp;
}
Encoder_class Encoder = Encoder_class();
}
