/*
 * I2Cclass.h
 *
 *  Created on: 6 февр. 2018 г.
 *      Author: anton.samoylov
 */
//TODO include stm32f0xx.h, stm32f0xx_rcc.h, stm32f0xx_gpio.h
#ifndef I2C_H_
#define I2C_H_
#include <main.h>
namespace HAL {

// Result of I2C procedures
typedef enum {
	I2C_ERROR = 0, I2C_SUCCESS = !I2C_ERROR
} I2C_Status;

// Send or not STOP condition
typedef enum {
	I2C_STOP = 0, I2C_NOSTOP = !I2C_STOP
} I2C_STOP_TypeDef;

// I2C defines
#define I2C_WAIT_TIMEOUT  (uint32_t)0x00005000 // Timeout for I2C operations
#define I2C_FLAG_MASK     (uint32_t)0x00FFFFFF // I2C flags mask (clear PEC register)

// I2C events
//#define I2C_EVENT_EV5     (uint32_t)(((I2C_SR2_BUSY | I2C_SR2_MSL) << 16) | I2C_SR1_SB)
//#define I2C_EVENT_EV6     ((uint32_t)((I2C_SR2_BUSY | I2C_SR2_MSL | I2C_SR2_TRA) << 16) | I2C_SR1_TXE | I2C_SR1_ADDR)
//#define I2C_EVENT_EV7     ((uint32_t)((I2C_SR2_BUSY | I2C_SR2_MSL) << 16) | I2C_SR1_RXNE)
#define I2C_EVENT_EV5     ((uint32_t)0x00030001) // BUSY, MSL, SB (MASTER_MODE_SELECT)
#define I2C_EVENT_EV6     ((uint32_t)0x00070082) // BUSY, MSL, TRA, TXE, ADDR (MASTER_TRANSMITTER_MODE_SELECTED)
#define I2C_EVENT_EV7     ((uint32_t)0x00030040) // BUSY, MSL, RXNE (MASTER_BYTE_RECEIVED)

// I2C flags (SR1 register)
#define I2C_F_RXNE        I2C_ISR_RXNE//((uint32_t)0x80000040) // Data register not empty
#define I2C_F_STOPF       I2C_ISR_STOPF//((uint32_t)0x80000010) // Stop detection
#define I2C_F_BTF         I2C_ISR_TC//((uint32_t)0x80000004) // Byte transfer finished
#define I2C_F_ADDR        ((uint32_t)0x80000002) // Address sent

// I2C flags (SR2 register)
#define I2C_F_BUSY        I2C_ISR_BUSY//((uint32_t)0x00000002) // Bus busy

class I2C_class {
private:
	I2C_TypeDef* I2Cx;
	I2C_Status waitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_Event);
	I2C_Status waitFlagSet(I2C_TypeDef* I2Cx, uint32_t I2C_Flag);
	I2C_Status waitFlagReset(I2C_TypeDef* I2Cx, uint32_t I2C_Flag);
public:
	I2C_class(I2C_TypeDef* I2Cx);
	I2C_Status init(uint32_t Clock);
	I2C_Status write(const uint8_t* buf, uint32_t nbytes, uint8_t SlaveAddress,
			I2C_STOP_TypeDef stop);
	I2C_Status read(uint8_t *buf, uint32_t nbytes, uint8_t SlaveAddress);
	I2C_Status isDeviceReady(uint8_t SlaveAddress, uint32_t Trials);
};

extern I2C_class I2C;
} /* namespace HAL */

#endif /* I2C_H_ */
