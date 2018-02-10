#pragma once
#include <main.h>
#include <HAL/Drivers/Flash.h>
namespace Settings {

#define SETTINGS_ADDRESS ((uint32_t)0x08003C00) //Конец памяти. Страница 15, сектор 3.
#define PAGE_SIZE ((uint32_t)0x400) //1 KByte
#define SETTINGS_END_ADDRESS ((uint32_t)(SETTINGS_ADDRESS+(PAGE_SIZE-1)) //Последний адрес страницы (0x08003FFF)

typedef struct {
	uint8_t maximumHumidity = 0;
	uint8_t currentHumidity = 0;
	uint32_t installedTime = 0;
	uint32_t currentTime = 0;
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
	void saveToMemory(param_t param);
};
extern Settings_class Parameters;
}

