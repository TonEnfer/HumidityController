#pragma once

#include <sys/_stdint.h>

namespace Settings {

#define SETTINGS_START_ADDRESS ((uint32_t)0x08003C00) //����� ������. �������� 15, ������ 3.
#define PAGE_SIZE ((uint32_t)0x400) //1 KByte
#define SETTINGS_END_ADDRESS ((uint32_t)(SETTINGS_START_ADDRESS+(PAGE_SIZE-1)) //��������� ����� �������� (0x08003FFF)

typedef struct {
	uint8_t maximumHumidity = 0;	//1 ����

} savableParam_t;

typedef struct {
	uint32_t installedTime = 5;		//4 ����
	uint32_t nodeShowTime = 5;		//4 ����
	uint8_t currentHumidity = 0;	//1 ����
									//3 - ��� ������������
} notSavableParam_t;

class Settings_class {
protected:
	savableParam_t sParam;
	notSavableParam_t nsParam;
public:
	Settings_class();

	uint32_t getNodeShowTime();
	void setNodeShowTime(uint32_t sht);
	void decNodeShowTime();

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

