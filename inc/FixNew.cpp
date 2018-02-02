/*
 * FixNew.cpp
 *
 *  Created on: 2 февр. 2018 г.
 *      Author: anton.samoylov
 */

#include "FixNew.h"
void *operator new(size_t size) {
	return malloc(size);
}

void *operator new[](size_t size) {
	return malloc(size);
}

void operator delete(void *p) {
	free(p);
}

void operator delete[](void *p) {
	free(p);
}


