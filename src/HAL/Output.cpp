/*
 * Output.cpp
 *
 *  Created on: 30 янв. 2018 г.
 *      Author: anton.samoylov
 */
// TODO Реализовать методы
#include <HAL/Output.h>
//Используется пин PB1
namespace HAL {
Output::Output() {

}
void Output::init() {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	GPIOB->MODER |= GPIO_MODER_MODER1_0;
	GPIOB->BSRR |= GPIO_BSRR_BR_1;
}
void Output::on() {
	GPIOB->BSRR |= GPIO_BSRR_BS_1;
}
void Output::off() {
	GPIOB->BSRR |= GPIO_BSRR_BR_1;
}

void Output::autoSwitch() {
	if ((Settings::Parameters.getCurHumidity()
			> Settings::Parameters.getMaxHumidity() + 3)
			|| (Settings::Parameters.getCurHumidity()
					< Settings::Parameters.getMaxHumidity() - 3))
		this->on();
	else
		this->off();
}
Output Out = Output();
}
