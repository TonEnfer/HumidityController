/*
 * PID.h
 *
 *  Created on: 22 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef PID_H_
#define PID_H_
#include <stm32f0xx.h>
#include <sys/_stdint.h>
#include <Settings.h>
#include <stddef.h>


class PID {
private:
	volatile uint32_t Kp, Ki, Kd;
	volatile uint32_t outValue;
public:
	PID(uint32_t Kp, uint32_t Ki, uint32_t Kd);
	void init();
	uint32_t getValue();
	void setValue(uint32_t outValue);
	uint32_t compute(uint32_t inputValue);
};
extern PID Regulator;
#endif /* PID_H_ */
