#include <FSM/FsmNode.h>
#include <HAL/BME280.h>
#include <HAL/Encoder.h>
#include <HAL/LedDisplay.h>
#include <HAL/Output.h>
#include <sys/_stdint.h>

LedDisplay display;
BME280 sensor;
Output out;
Encoder enc;

FsmNode showCurHum, showSetHum, editSetHum, showSetTime, editSetTime,
		showCurTime;
FsmNode* currentNode = &showCurHum;

uint8_t curHum;
uint8_t maxHum = 80;
uint8_t curTime = 15;

void regulate() {
	if (curHum > maxHum)
		out.on();
	else
		out.off();
}

int8_t calcTime(int encPosition) {
	return 0;
}

int8_t calcHum(int encPosition)
{
	return 0;
}

void enterShowCurHum() {
	curHum = sensor.getHum();
	display.show(curHum);
	regulate();
}

void switchShowCurHum() {
	if (enc.press())
		currentNode = FsmNode::switchNode(currentNode, &showCurTime);
	else if (enc.rotate()) {
		calcTime(enc.getPosition());

	} else {
		curHum = sensor.getHum();
		display.show(curHum);
		regulate();
	}
}


void init() {
	display.init();
	showCurHum.NodeEnterFunction = &enterShowCurHum;
	showCurHum.NodeEnterFunction = &switchShowCurHum;
}

int main(void) {
	init();
	while (true) {
		currentNode->NodeSwitchFunction();
	}
}
