/*
 * system.cpp
 *
 *  Created on: 18 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include "stm32f0xx.h"


uint32_t SystemCoreClock = 48000000;
__I uint8_t AHBPrescTable[16] =
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9 };

void SystemCoreClockUpdate(void) {
	uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0;

	/* Get SYSCLK source -------------------------------------------------------*/
	tmp = RCC->CFGR & RCC_CFGR_SWS;

	switch (tmp) {
	case 0x00: /* HSI used as system clock */
		SystemCoreClock = HSI_VALUE;
		break;
	case 0x04: /* HSE used as system clock */
		SystemCoreClock = HSE_VALUE;
		break;
	case 0x08: /* PLL used as system clock */
		/* Get PLL clock source and multiplication factor ----------------------*/
		pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
		pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
		pllmull = (pllmull >> 18) + 2;

		if (pllsource == 0x00) {
			/* HSI oscillator clock divided by 2 selected as PLL clock entry */
			SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
		} else {
			prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
			/* HSE oscillator clock selected as PREDIV1 clock entry */
			SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull;
		}
		break;
	default: /* HSI used as system clock */
		SystemCoreClock = HSI_VALUE;
		break;
	}
	/* Compute HCLK clock frequency ----------------*/
	/* Get HCLK prescaler */
	tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
	/* HCLK clock frequency */
	SystemCoreClock >>= tmp;
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
