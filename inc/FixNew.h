/*
 * FixNew.h

 *
 *  Created on: 1 ����. 2018 �.
 *      Author: anton.samoylov
 */
#pragma once
#include <stdlib.h>
//#include "stm32f0xx.h"

using namespace std;

void *operator new(size_t size);

void *operator new[](size_t size);

void operator delete(void *p);

void operator delete[](void *p);



