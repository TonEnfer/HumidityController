/*
 * interrupts.h
 *
 *  Created on: 14 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

extern "C" void NMI_Handler(void);
extern "C" void HardFault_Handler(void);
extern "C" void SVC_Handler(void);
extern "C" void PendSV_Handler(void);
extern "C" void WWDG_IRQHandler() {
}

extern "C" void PVD_IRQHandler() {
}

extern "C" void RTC_IRQHandler() {
}

extern "C" void FLASH_IRQHandler() {
}

extern "C" void RCC_IRQHandler() {
}

extern "C" void EXTI2_3_IRQHandler() {
}

extern "C" void EXTI4_15_IRQHandler() {
}

extern "C" void DMA1_CH1_IRQHandler() {
}

extern "C" void DMA1_CH2_3_IRQHandler() {
}

extern "C" void DMA1_CH4_5_IRQHandler() {
}

extern "C" void ADC_IRQHandler() {
}

extern "C" void TIM1_BRK_UP_TRG_COM_IRQHandler() {
}

extern "C" void TIM1_CC_IRQHandler() {
}

extern "C" void TIM17_IRQHandler() {
}

extern "C" void I2C1_IRQHandler() {
}

extern "C" void SPI1_IRQHandler() {
}

extern "C" void USART1_IRQHandler() {
}

//extern "C" void Reset_Handler(void);

#endif /* INTERRUPTS_H_ */
