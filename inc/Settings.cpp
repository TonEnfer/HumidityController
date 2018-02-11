/*
 * Settings.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <Settings.h>

namespace Settings {
Settings_class::Settings_class() {
	param.currentHumidity = 0;
	param.currentTime = 0;
	param.installedTime = 5;
	param.maximumHumidity = 50;
}

uint8_t Settings_class::getMaxHumidity() {
	return param.maximumHumidity;
}
void Settings_class::setMaxHumidity(uint8_t hum) {
	param.maximumHumidity = hum;
	this->saveToMemory();
}

uint8_t Settings_class::getCurHumidity() {
	return param.currentHumidity;
}
void Settings_class::setCurHumidity(uint8_t hum) {
	param.currentHumidity = hum;
}

uint32_t Settings_class::getInsTime() {
	return param.installedTime;
}
void Settings_class::setInstTime(uint32_t time) {
	param.installedTime = time;
}

uint32_t Settings_class::getCurTime() {
	return param.currentTime;
}
void Settings_class::setCurTime(uint32_t time) {
	param.currentTime = time;
}

uint8_t Settings_class::normalize(uint8_t value) {
	if (value > 100)
		return 99;
	else
		return value;
}

void Settings_class::restoreFromMemory() {
	//TODO Разобраться на реальном железе
	uint16_t data[sizeof(param_t)] = { };
	__IO uint32_t addr = SETTINGS_START_ADDRESS;
	for (uint8_t i = 0; i < sizeof(param_t); i++) {
		data[i] = (*(__IO uint16_t*) addr);
		addr += 2;
	}
	uint16_t *p = (uint16_t *) &param;
	for (uint8_t i = 0; i < sizeof(param_t); i++) {
		*p = data[i];
		p++;
	}
}

void Settings_class::saveToMemory() {
	HAL::Flash.erasePage(SETTINGS_START_ADDRESS);	//Очищаем страницу
	uint16_t *tmp = (uint16_t *) &param;
	for (uint8_t i = 0; i < sizeof(param_t); i++) {	//Записываем в память по 16 бит
		HAL::Flash.programHalfWord(SETTINGS_START_ADDRESS + 2 * i, *tmp++);
	}
}

Settings_class Parameters = Settings_class();
}

