/*
 * main.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <main.h>

#include <FSM/FinalStateMashine.h>
#include <Settings.h>
#include <HAL/BME280.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>
#include <HAL/Encoder.h>

uint32_t SystemCoreClock = 48000000;

FSM::FinalStateMashine fsm;
int main() {
	fsm = FSM::FinalStateMashine();

	HAL::Display.init();
	HAL::Encoder.init();
	HAL::Out.init();
	HAL::Sensor.init();

	__enable_irq();
	while (true) {
		fsm.run();
		delay_us(100);
	}
	return 0;
}

void SystemInit() {

//	/* Reset the RCC clock configuration to the default reset state ------------*/
//	/* Set HSION bit */
//	RCC->CR |= (uint32_t) 0x00000001U;
//
//#if defined (STM32F051x8) || defined (STM32F058x8)
//	/* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
//	RCC->CFGR &= (uint32_t)0xF8FFB80CU;
//#else
//	/* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
//	RCC->CFGR &= (uint32_t) 0x08FFB80CU;
//#endif /* STM32F051x8 or STM32F058x8 */
//
//	/* Reset HSEON, CSSON and PLLON bits */
//	RCC->CR &= (uint32_t) 0xFEF6FFFFU;
//
//	/* Reset HSEBYP bit */
//	RCC->CR &= (uint32_t) 0xFFFBFFFFU;
//
//	/* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
//	RCC->CFGR &= (uint32_t) 0xFFC0FFFFU;
//
//	/* Reset PREDIV[3:0] bits */
//	RCC->CFGR2 &= (uint32_t) 0xFFFFFFF0U;
//
//	/* Reset USART1SW[1:0], I2C1SW and ADCSW bits */
//	RCC->CFGR3 &= (uint32_t) 0xFFFFFEECU;
//
//	/* Reset HSI14 bit */
//	RCC->CR2 &= (uint32_t) 0xFFFFFFFEU;
//
//	/* Disable all interrupts */
//	RCC->CIR = 0x00000000U;

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

