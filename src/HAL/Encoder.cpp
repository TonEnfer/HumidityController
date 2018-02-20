/*
 * encoder.cpp
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */
// TODO ��������� ������
#include <HAL/Encoder.h>

extern "C" void EXTI0_1_IRQHandler() {
	static uint8_t oldA, oldB;
	//delay_us(1);
	volatile uint8_t A = HAL::GPIO::readInputDataBit(GPIOF, GPIO_IDR_0);
	//delay_us(1);
	volatile uint8_t B = HAL::GPIO::readInputDataBit(GPIOF, GPIO_IDR_1);
	if (oldA ^ oldB ^ A ^ B) {
		if (oldA ^ B)
			HAL::Encoder.position--;
		else
			HAL::Encoder.position++;
	}
	oldA = A;
	oldB = B;
	EXTI->PR |= EXTI_PR_PR0 | EXTI_PR_PR1;
}

#define BUTTON_PRESSED 0
volatile static uint8_t oldState = 0;
volatile static bool longPressDetected = false;
volatile static uint16_t pressedPeriods = 0;
#define BUTTON_PERIOD 100
#define BUTTON_SHORT_PERIOD 10
#define BUTTON_LONG_PERIOD 5000
extern "C" void TIM14_IRQHandler() {
	uint8_t newState = HAL::GPIO::readInputDataBit(GPIOA, GPIO_IDR_0);

	if (oldState == BUTTON_PRESSED) {
		if (pressedPeriods * BUTTON_PERIOD >= BUTTON_LONG_PERIOD) {
			if (longPressDetected) {
				if (newState != BUTTON_PRESSED) {
					pressedPeriods = 0;
					longPressDetected = false;
				}
			} else {
				HAL::Encoder.longPres = true;
				HAL::Encoder.pres = false;
				longPressDetected = true;
			}
		} else if (newState != BUTTON_PRESSED) {
			if (pressedPeriods * BUTTON_PERIOD >= BUTTON_SHORT_PERIOD) {
				HAL::Encoder.pres = true;
				HAL::Encoder.longPres = false;
				pressedPeriods = 0;
			} else {
				HAL::Encoder.pres = false;
				HAL::Encoder.longPres = false;
				pressedPeriods = 0;
			}
		} else if (newState == BUTTON_PRESSED) {
			pressedPeriods++;
		}
	} else {
		if (newState == BUTTON_PRESSED) {
			pressedPeriods = 1;
		} else {
			//DO nothing
		}
	}

	oldState = newState;
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

	NVIC_SetPriority(EXTI0_1_IRQn, 3);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR1;

	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->DIER |= TIM_DIER_UIE;
	TIM14->PSC = (uint16_t) (SystemCoreClock/375000)-1; //375 kHz
	TIM14->ARR = (uint16_t) 37500; //100 ms
	TIM14->CNT = (uint16_t) 0; //Reset count val
	TIM14->EGR |= TIM_EGR_UG; //UPDATE auto-reload value;
	TIM14->CR1 |= TIM_CR1_URS | TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM14->SR &= ~0xFFFF;
	NVIC_SetPriority(TIM14_IRQn, 3);
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

bool Encoder_class::isRotated() {
	if(position != 0)
		return true;
	else
		return false;
}

int Encoder_class::getPosition() {
	int tmp = this->position;
	this->position = 0;
	return tmp;
}
Encoder_class Encoder = Encoder_class();
}
