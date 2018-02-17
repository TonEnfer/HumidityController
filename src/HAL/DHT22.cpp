/*
 * DHT22.cpp
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/DHT22.h>
// TODO ����������� ������
namespace HAL {

DHT22::DHT22() {

}
void DHT22::init() {
	//	RCC_APB2PeriphClockCmd(DHT22_GPIO_CLOCK, ENABLE);
//	PORT.GPIO_Mode = GPIO_Mode_Out_PP;
//	PORT.GPIO_Pin = DHT22_GPIO_PIN;
//	PORT.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(DHT22_GPIO_PORT, &PORT);
}

uint32_t DHT22::getReadings(void) {
	uint32_t wait;
	uint8_t i;

	// Generate start impulse for sensor
	DHT22_GPIO_PORT->BRR = DHT22_GPIO_PIN; // Pull down SDA (Bit_SET)
	delay_ms(2); // Host start signal at least 800us
	DHT22_GPIO_PORT->BSRR = DHT22_GPIO_PIN; // Release SDA (Bit_RESET)
//	PORT.GPIO_Mode = GPIO_Mode_IPU; // Switch pin to input with Pull-Up
//	GPIO_Init(DHT22_GPIO_PORT, &PORT);

	// Wait for AM2302 to start communicate
	wait = 0;
	while ((DHT22_GPIO_PORT->IDR & DHT22_GPIO_PIN) == (uint32_t) 1
			&& (wait++ < 200))
		delay_us(2);
	if (wait > 50)
		return DHT22_RCV_NO_RESPONSE;

	// Check ACK strobe from sensor
	wait = 0;
	while (((DHT22_GPIO_PORT->IDR & DHT22_GPIO_PIN) == (uint32_t) 0)
			&& (wait++ < 100))
		delay_us(1);
	if ((wait < 8) || (wait > 15))
		return DHT22_RCV_BAD_ACK1;

	wait = 0;
	while (((DHT22_GPIO_PORT->IDR & DHT22_GPIO_PIN) == (uint32_t) 1)
			&& (wait++ < 100))
		delay_us(1);
	if ((wait < 8) || (wait > 15))
		return DHT22_RCV_BAD_ACK2;

	// ACK strobe received --> receive 40 bits
	i = 0;
	while (i < 40) {
		// Measure bit start impulse (T_low = 50us)
		wait = 0;
		while (((DHT22_GPIO_PORT->IDR & DHT22_GPIO_PIN) == (uint32_t) 0)
				&& (wait++ < 20))
			delay_us(1);
		if (wait > 16) {
			// invalid bit start impulse length
			bits[i] = 0xffff;
			while (((DHT22_GPIO_PORT->IDR & DHT22_GPIO_PIN) == (uint32_t) 1)
					&& (wait++ < 20))
				delay_us(1);
		} else {
			// Measure bit impulse length (T_h0 = 25us, T_h1 = 70us)
			wait = 0;
			while (((DHT22_GPIO_PORT->IDR & DHT22_GPIO_PIN) == (uint32_t) 1)
					&& (wait++ < 20))
				delay_us(1);
			bits[i] = (wait < 16) ? wait : 0xffff;
		}

		i++;
	}

	for (i = 0; i < 40; i++)
		if (bits[i] == 0xffff)
			return DHT22_RCV_RCV_TIMEOUT;

	return DHT22_RCV_OK;
}

uint16_t DHT22::decodeReadings(void) {
	uint8_t parity;
	uint8_t i = 0;

	hMSB = 0;
	for (; i < 8; i++) {
		hMSB <<= 1;
		if (bits[i] > 7)
			hMSB |= 1;
	}
	hLSB = 0;
	for (; i < 16; i++) {
		hLSB <<= 1;
		if (bits[i] > 7)
			hLSB |= 1;
	}
	tMSB = 0;
	for (; i < 24; i++) {
		tMSB <<= 1;
		if (bits[i] > 7)
			tMSB |= 1;
	}
	tLSB = 0;
	for (; i < 32; i++) {
		tLSB <<= 1;
		if (bits[i] > 7)
			tLSB |= 1;
	}
	for (; i < 40; i++) {
		parity_rcv <<= 1;
		if (bits[i] > 7)
			parity_rcv |= 1;
	}

	parity = hMSB + hLSB + tMSB + tLSB;

	return (parity_rcv << 8) | parity;
}

uint16_t DHT22::getHumidity(void) {
	return (hMSB << 8) + hLSB;
}

uint16_t DHT22::getTemperature(void) {
	return (tMSB << 8) + tLSB;
}

#ifdef USE_DHT22
Sensor_class *Sensor = new DHT22();
#endif

}
/* namespace HAL */
