/*
 * Output.h
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "stm32f0xx.h"
namespace HAL {
class Output {
public:
	Output();
	void on();
	void off();
};
}
#endif /* OUTPUT_H_ */
