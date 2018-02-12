#pragma once
#include <main.h>
#include <HAL/Drivers/Flash.h>
namespace Settings {

#define SETTINGS_START_ADDRESS ((uint32_t)0x08003C00) //Конец памяти. Страница 15, сектор 3.
#define PAGE_SIZE ((uint32_t)0x400) //1 KByte
#define SETTINGS_END_ADDRESS ((uint32_t)(SETTINGS_START_ADDRESS+(PAGE_SIZE-1)) //Последний адрес страницы (0x08003FFF)

typedef struct {
	uint32_t installedTime = 5;		//4 байт
	uint32_t currentTime = 0;		//4 байт
	uint8_t maximumHumidity = 0;	//1 байт
	uint8_t currentHumidity = 0;	//1 байт
									//2 - для выравнивания
} param_t;

class Settings_class {
protected:
	param_t param;
public:
	Settings_class();

	uint8_t getMaxHumidity();
	void setMaxHumidity(uint8_t hum);

	uint8_t getCurHumidity();
	void setCurHumidity(uint8_t hum);

	uint32_t getInsTime();
	void setInstTime(uint32_t time);

	uint32_t getCurTime();
	void setCurTime(uint32_t time);

	uint8_t normalize(uint8_t value);

	void restoreFromMemory();
	void saveToMemory();
};
extern Settings_class Parameters;
}

