#include <FSM/FsmNode.h>
#include <HAL/LedDisplay.h>
#include <HAL/BME280.h>
#include <HAL/Output.h>
#include "stm32f0xx.h"
#include <math.h>

LedDisplay display;
BME280 sensor;
Output out;

FsmNode showCurHum,showSetHum,editSetHum,showSetTime,editSetTime,showCurTime;
FsmNode* currentNode = &showCurHum;

uint8_t curHum;
uint8_t maxHum = 80;

void showCurrentHumidity()
{
	curHum = sensor.getHum();
	display.show(curHum);
	regulate();
}

void regulate()
{
	if(curHum > maxHum)
		out.on();
	else out.off();
}


void init()
{
	display.init();
	showCurHum.NodeEnterFunction = &showCurrentHumidity;
}

int main(void)
{
	init();
	while(true)
	{

	}
}
