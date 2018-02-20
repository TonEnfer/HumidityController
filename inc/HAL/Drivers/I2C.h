/*
 * I2Cclass.h
 *
 *  Created on: 6 ����. 2018 �.
 *      Author: anton.samoylov
 */
//TODO include stm32f0xx.h, stm32f0xx_rcc.h, stm32f0xx_gpio.h
#ifndef I2C_H_
#define I2C_H_

#include <main.h>
#include <HAL/Drivers/GPIO.h>
#include <HAL/LedDisplay.h>

namespace HAL {

#define I2C_BUS I2C1

typedef enum {
	I2C_ERROR = 0, I2C_SUCCESS = !I2C_ERROR
} I2C_Status;

typedef enum {
	I2C_STOP = 0, I2C_NOSTOP = !I2C_STOP
} I2C_STOP_TypeDef;

typedef enum _I2C_Direction {
	I2C_Transmitter = 0, I2C_Receiver = 1
} I2C_Direction;

#define I2C_OFFSET_TIMINGR_SCLL		0
#define I2C_OFFSET_TIMINGR_SCLH		8
#define I2C_OFFSET_TIMINGR_SDADEL	16
#define I2C_OFFSET_TIMINGR_SCLDEL	20
#define I2C_OFFSET_TIMINGR_PRESC	28
#define I2C_OFFSET_CR2_NBYTES		16

class I2C_class {
private:
	void start(void);
	void stop(void);
	void startDirectionAdressSize(I2C_Direction Direction, uint8_t Adress,
			uint8_t Size);
public:
	void init(void);
	I2C_Status write(uint8_t addr, uint8_t reg, uint8_t *data,
			uint8_t size);
	I2C_Status read(uint8_t addr, uint8_t reg, uint8_t *data,
			uint8_t size);
};
extern I2C_class I2C;
}/* namespace HAL */

#endif /* I2C_H_ */
