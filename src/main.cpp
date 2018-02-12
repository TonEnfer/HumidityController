/*
 * main.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <main.h>

#include <FSM/FinalStateMashine.h>
#include <Settings.h>

uint32_t SystemCoreClock = 48000000;

void SystemInit() {

	FLASH->ACR |= FLASH_ACR_PRFTBE;
	FLASH->ACR &= (uint32_t) ((uint32_t) ~FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t) 0x01;
	/* HCLK = SYSCLK */
	RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV1;
	/* PCLK1 = HCLK */
	RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE_DIV1;
	//Сбрасываем настройки PLL
	RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE
			| RCC_CFGR_PLLMUL));
	/*Устанавливаем источник PLL = HSI/2 и PLL Mul = 12*/
	RCC->CFGR |= (uint32_t) (RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12);
	/* Включаем PLL */
	RCC->CR |= RCC_CR_PLLON;
	//Ждём готовности PLL
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
	}
	//Устанавливаем PLL в качестве источника тактирования
	RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;
	//Ждём готовности
	while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08) {
	}

}

FSM::FinalStateMashine fsm;
volatile uint8_t a = 0;
int main() {
	fsm = FSM::FinalStateMashine();
	Settings::Parameters.setCurHumidity(10);
	Settings::Parameters.setCurTime(6666);

	while (true) {
		a++;
	}
	return 0;
}

