/*
 * FixNew.h

 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */
#pragma once
#include <main.h>

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);

