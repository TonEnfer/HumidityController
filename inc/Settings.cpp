/*
 * Settings.cpp
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include <Settings.h>

namespace Settings {
Settings_class::Settings_class()
{
param.currentHumidity = 0;
param.currentTime = 0;
param.installedTime = 5;
param.maximumHumidity = 50;
}

uint8_t Settings_class::getMaxHumidity(){
	return param.maximumHumidity;
}
void Settings_class::setMaxHumidity(uint8_t hum){
	param.maximumHumidity = hum;
	//TODO Добавить сохранение в память
}

uint8_t Settings_class::getCurHumidity(){
	return param.currentHumidity;
}
void Settings_class::setCurHumidity(uint8_t hum){
	param.currentHumidity = hum;
}

uint32_t Settings_class::getInsTime(){
	return param.installedTime;
}
void Settings_class::setInstTime(uint32_t time){
	param.installedTime = time;
}

uint32_t Settings_class::getCurTime(){
	return param.currentTime;
}
void Settings_class::setCurTime(uint32_t time){
	param.currentTime = time;
}

uint8_t Settings_class::normalize(uint8_t value) {
	if (value > 100)
		return 99;
	else
		return value;
}

void Settings_class::restoreFromMemory(){
	//TODO Разобраться на реальном железе
	volatile uint32_t tmpData[sizeof(param_t)];
	__IO uint32_t tmp = SETTINGS_ADDRESS;
	for(uint16_t i =0;i<sizeof(param_t);i++){
		tmpData[i] = (*(__IO uint32_t*)tmp);
		tmp+=4;
	}
}


void Settings_class::saveToMemory(param_t param)
{
	//TODO Разобраться на реальном железе
	HAL::Flash.erasePage(SETTINGS_ADDRESS);

	for(uint16_t i = 0; i < sizeof(param_t); i++)
	{
		HAL::Flash.programHalfWord(SETTINGS_ADDRESS+4*i,15);
	}
}

void Settings_class::saveToMemory()
{
	saveToMemory(this->param);
}

Settings_class Parameters = Settings_class();
}


