#pragma once
#include "stm32f0xx.h"
namespace Settings {

volatile static char maximumHumidity = 50;
volatile static char currentHumidity = 0;
volatile static char installedTime = 5;
volatile static char currentTime = 0;

char normalize(char value);
}

