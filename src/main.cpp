/*
 * main.cpp
 *
 *  Created on: 10 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <main.h>

#include <FSM/FinalStateMashine.h>
#include <Settings.h>

uint32_t SystemCoreClock = 48000000;

FSM::FinalStateMashine fsm;
volatile uint8_t a = 0;
int main() {
	fsm = FSM::FinalStateMashine();

	while (true) {
		fsm.run();
		delay_us(15);
	}
	return 0;
}

void SystemInit() {

	FLASH->ACR |= FLASH_ACR_PRFTBE;
	FLASH->ACR &= (uint32_t) ((uint32_t) ~FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t) 0x01;
	/* HCLK = SYSCLK */
	RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV1;
	/* PCLK1 = HCLK */
	RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE_DIV1;
	//���������� ��������� PLL
	RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE
			| RCC_CFGR_PLLMUL));
	/*������������� �������� PLL = HSI/2 � PLL Mul = 12*/
	RCC->CFGR |= (uint32_t) (RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12);
	/* �������� PLL */
	RCC->CR |= RCC_CR_PLLON;
	//��� ���������� PLL
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
	}
	//������������� PLL � �������� ��������� ������������
	RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;
	//��� ����������
	while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08) {
	}
}

