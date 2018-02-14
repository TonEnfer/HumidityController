/*
 * interrupts.h
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <main.h>

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void Reset_Handler(void);


#endif /* INTERRUPTS_H_ */
