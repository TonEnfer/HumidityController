#pragma once
#include <main.h>

namespace Settings {

typedef struct {
	uint8_t maximumHumidity = 0;
	uint8_t currentHumidity = 0;
	uint32_t installedTime = 0;
	uint32_t currentTime = 0;
}param_t;

class Settings_class {
protected:
	param_t param;
	void saveToMemory(param_t *param);
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

	param_t restoreFromMemory();
};
extern Settings_class Parameters;
}

