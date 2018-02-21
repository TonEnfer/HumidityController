/*
 * DHT22.h
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef DHT22_H_
#define DHT22_H_

#include <HAL/Sensor.h>
#include <sys/_stdint.h>
#include <stm32f0xx.h>

/* Port and pin with DHT22 sensor*/
#define DHT22_GPIO_PORT            GPIOB
#define DHT22_GPIO_CLOCK           RCC_APB2Periph_GPIOB
#define DHT22_GPIO_PIN             0

/* DHT22_GetReadings response codes */
#define DHT22_RCV_OK               0 // Return with no error
#define DHT22_RCV_NO_RESPONSE      1 // No response from sensor
#define DHT22_RCV_BAD_ACK1         2 // Bad first half length of ACK impulse
#define DHT22_RCV_BAD_ACK2         3 // Bad second half length of ACK impulse
#define DHT22_RCV_RCV_TIMEOUT      4 // It was timeout while receiving bits

namespace HAL {

class DHT22: public Sensor_class {
public:
	DHT22();
	void init();
	uint16_t getHumidity();
	uint16_t getTemperature();
	~DHT22() {
	}
	;

private:
	uint16_t bits[40];

	uint8_t hMSB = 0;
	uint8_t hLSB = 0;
	uint8_t tMSB = 0;
	uint8_t tLSB = 0;
	uint8_t parity_rcv = 0;

	uint32_t getReadings(void);
	uint16_t decodeReadings(void);
};

} /* namespace HAL */

#endif /* DHT22_H_ */
