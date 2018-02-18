/*
 * I2Cclass.cpp
 *
 *  Created on: 6 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/I2C.h>

namespace HAL {

/*
 Выполняет первичную настройку шины.
 Настраивает порты, альтернативные функции.
 Настраивает тайминги для работы шины.
 */
void I2C_class::init(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;		// Включаю тактирование I2C
	// Настройка ног PB6, PB7
	GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;	// Режим альтернативной функции
	GPIOA->OTYPER |= GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10;// Открытый коллектор
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9 | GPIO_OSPEEDR_OSPEEDR10;// Максимальная скорость
	// Выбор альтернативной функции
	HAL::GPIO::pinAFConfig(GPIOB, 6, 1);	// I2C1_SCL
	HAL::GPIO::pinAFConfig(GPIOB, 6, 1);	// I2C1_SDA

	I2C_BUS->CR1 &= ~I2C_CR1_PE;			// Отключаю I2C
	while (I2C_BUS->CR1 & I2C_CR1_PE) {
	};	// Жду пока отключится

	// Частота тактирования модуля I2C = 48 МГц
	// Частота шины I2C = 100 kHz
	// Настраиваю тайминги
	I2C_BUS->TIMINGR |= (0xB << I2C_OFFSET_TIMINGR_PRESC)
			| (0x13 << I2C_OFFSET_TIMINGR_SCLL)
			| (0xF << I2C_OFFSET_TIMINGR_SCLH)
			| (0x4 << I2C_OFFSET_TIMINGR_SCLDEL)
			| (0x2 << I2C_OFFSET_TIMINGR_SDADEL);

	I2C_BUS->CR1 |= I2C_CR1_PE;					// Включаю I2C
	while ((I2C_BUS->CR1 & I2C_CR1_PE) == 0) {
	};	// Жду пока включится
}

/*
 Это служебная функция, использовать её не нужно.
 Устанавливает направление данных - приём или передача.
 Задаёт объём пересылаемых данных.
 Задаёт адрес ведомого устройства.
 Выдаёт старт на шину.
 Параметры:
 Direction - направление (0-отправка, 1-приём)
 Adress - адрес ведомого устройства
 Size - размер данных (от 1 до 255 байт)
 */
void I2C_class::startDirectionAdressSize(I2C_Direction Direction,
		uint8_t Adress, uint8_t Size) {
	//I2C_BUS->CR2 &= ~I2C_CR2_AUTOEND;				// Выдавать стоп вручную
	//I2C_BUS->CR2 &= ~I2C_CR2_RELOAD;				// Не использовать режим перезагрузки
	if (Direction)
		I2C_BUS->CR2 |= I2C_CR2_RD_WRN;	// Режим приёма
	else
		I2C_BUS->CR2 &= ~I2C_CR2_RD_WRN;			// Режим передачи
	I2C_BUS->CR2 &= ~I2C_CR2_NBYTES;				// Очистить размер данных
	I2C_BUS->CR2 |= Size << I2C_OFFSET_CR2_NBYTES;	// Установить размер данных
	I2C_BUS->CR2 &= ~I2C_CR2_SADD;	// Очистить адрес ведомого устройства
	I2C_BUS->CR2 |= Adress;			// Установить адрес ведомого устройства
	I2C_BUS->CR2 |= I2C_CR2_START;					// Выдать старт на шину
	while ((I2C_BUS->ISR & I2C_ISR_BUSY) == 0) {
	};	// Ожидать выдачу старта
}

/*
 Это служебная функция, использовать её не нужно.
 Выдаёт стоп на шину.
 Очищает флаги.
 Проверяет наличие ошибок, очищает флаги ошибок.
 */
void I2C_class::stop(void) {
	I2C_BUS->CR2 |= I2C_CR2_STOP;				// Выдать стоп на шину
	while (I2C_BUS->ISR & I2C_ISR_BUSY) {
	};		// Ожидать выдачу стопа
	// Очищаю флаги - необходимо для дальнейшей работы шины
	I2C_BUS->ICR |= I2C_ICR_STOPCF;		// STOP флаг
	I2C_BUS->ICR |= I2C_ICR_NACKCF;		// NACK флаг
	// Если есть ошибки на шине - очищаю флаги
	if (I2C_BUS->ISR & (I2C_ISR_ARLO | I2C_ISR_BERR)) {
		I2C_BUS->ICR |= I2C_ICR_ARLOCF;
		I2C_BUS->ICR |= I2C_ICR_BERRCF;
	}
}

/*
 Выполняет транзакцию записи Size байт в регистр Register по адресу Adress.
 Параметры:
 Adress - адрес ведомого устройства
 Register - регистр, в который хотим передать данные
 Data - указывает откуда брать данные для передачи
 Size - сколько байт хотим передать (от 1 до 254)
 Возвращает:
 1 - если данные успешно переданы
 0 - если произошла ошибка
 */
I2C_Status I2C_class::write(uint8_t addr, uint8_t reg, uint8_t *data,
		uint8_t size) {
	uint8_t Count = 0;	// Счётчик успешно переданных байт
	// Старт
	startDirectionAdressSize(I2C_Transmitter, addr, 1 + size);
	// Сейчас либо I2C запросит первый байт для отправки,
	// Либо взлетит NACK-флаг, говорящий о том, что микросхема не отвечает.
	// Если взлетит NACK-флаг, отправку прекращаем.
	while ((((I2C_BUS->ISR & I2C_ISR_TXIS) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
	};
	if (I2C_BUS->ISR & I2C_ISR_TXIS)
		I2C_BUS->TXDR = reg;	// Отправляю адрес регистра

	// Отправляем байты до тех пор, пока не взлетит TC-флаг.
	// Если взлетит NACK-флаг, отправку прекращаем.
	while ((((I2C_BUS->ISR & I2C_ISR_TC) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
		if (I2C_BUS->ISR & I2C_ISR_TXIS)
			I2C_BUS->TXDR = *(data + Count++);	// Отправляю данные
	}
	stop();
	if (Count == size)
		return I2C_SUCCESS;
	return I2C_ERROR;
}

/*
 Выполняет транзакцию чтения Size байт из регистра Register по адресу Adress.
 Параметры:
 Adress - адрес ведомого устройства
 Register - регистр, из которого хотим принять данные
 Data - указывает куда складывать принятые данные
 Size - сколько байт хотим принять (от 1 до 255)
 Возвращает:
 1 - если данные успешно приняты
 0 - если произошла ошибка
 */
I2C_Status I2C_class::read(uint8_t addr, uint8_t reg, uint8_t *data,
		uint8_t size) {
	uint8_t Count = 0;	// Счётчик успешно принятых байт
	// Старт
	startDirectionAdressSize(I2C_Transmitter, addr, 1);
	// Сейчас либо I2C запросит первый байт для отправки,
	// Либо взлетит NACK-флаг, говорящий о том, что микросхема не отвечает.
	// Если взлетит NACK-флаг, отправку прекращаем.
	while ((((I2C_BUS->ISR & I2C_ISR_TC) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
		if (I2C_BUS->ISR & I2C_ISR_TXIS)
			I2C_BUS->TXDR = reg;	// Отправляю адрес регистра
	}
	// Повторный старт
	startDirectionAdressSize(I2C_Receiver, addr, size);
	// Принимаем байты до тех пор, пока не взлетит TC-флаг.
	// Если взлетит NACK-флаг, приём прекращаем.
	while ((((I2C_BUS->ISR & I2C_ISR_TC) == 0)
			&& ((I2C_BUS->ISR & I2C_ISR_NACKF) == 0))
			&& (I2C_BUS->ISR & I2C_ISR_BUSY)) {
		if (I2C_BUS->ISR & I2C_ISR_RXNE)
			*(data + Count++) = I2C_BUS->RXDR;	// Принимаю данные
	}
	stop();
	if (Count == size)
		return I2C_SUCCESS;
	return I2C_ERROR;
}

I2C_class I2C = I2C_class();
} /* namespace HAL */
