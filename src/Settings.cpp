/*
 * Settings.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <Settings.h>

namespace Settings {
Settings_class::Settings_class() {
	nsParam.currentHumidity = 8;
	nsParam.installedTime = (3*60)-1;
	sParam.maximumHumidity = 53;
	nsParam.nodeShowTime = 5;
}
uint32_t Settings_class::getNodeShowTime(){
	return nsParam.nodeShowTime;
}
void Settings_class::setNodeShowTime(uint32_t sht){
	nsParam.nodeShowTime = sht;
}

void Settings_class::decNodeShowTime(){
	if(nsParam.nodeShowTime != 0)
		nsParam.nodeShowTime--;
}

uint8_t Settings_class::getMaxHumidity() {
	return sParam.maximumHumidity;
}
void Settings_class::setMaxHumidity(uint8_t hum) {
	sParam.maximumHumidity = hum;
	this->saveToMemory();
}

uint8_t Settings_class::getCurHumidity() {
	return nsParam.currentHumidity;
}
void Settings_class::setCurHumidity(uint8_t hum) {
	nsParam.currentHumidity = hum;
}

uint32_t Settings_class::getInsTime() {
	return nsParam.installedTime;
}
void Settings_class::setInstTime(uint32_t time) {
	nsParam.installedTime = time;
}

uint8_t Settings_class::normalize(uint8_t value) {
	if (value > 100)
		return 99;
	else
		return value;
}

void Settings_class::restoreFromMemory() {
	uint16_t data[sizeof(savableParam_t)] = { };
	__IO uint32_t addr = SETTINGS_START_ADDRESS;
	for (uint8_t i = 0; i < sizeof(savableParam_t); i++) {
		data[i] = (*(__IO uint16_t*) addr);
		addr += 2;
	}
	uint16_t *p = (uint16_t *) &sParam;
	for (uint8_t i = 0; i < sizeof(savableParam_t); i++) {
		*p = data[i];
		p++;
	}
}

void Settings_class::saveToMemory() {
	HAL::Flash.unlock();
	HAL::Flash.erasePage(SETTINGS_START_ADDRESS);	//Очищаем страницу
	uint16_t *tmp = (uint16_t *) &sParam;
	for (uint8_t i = 0; i < sizeof(savableParam_t); i++) {	//Записываем в память по 16 бит
		HAL::Flash.programHalfWord(SETTINGS_START_ADDRESS + 2 * i, *tmp++);
	}
	HAL::Flash.lock();
}

Settings_class Parameters = Settings_class();
}

