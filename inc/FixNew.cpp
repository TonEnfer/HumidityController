/*
 * FixNew.cpp
 *
 *  Created on: 2 ����. 2018 �.
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


