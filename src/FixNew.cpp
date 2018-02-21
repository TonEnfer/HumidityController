/*
 * FixNew.cpp
 *
 *  Created on: 2 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <FixNew.h>
#include <stdlib.h>

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

void operator delete(void* p, unsigned int size) {
	(void) (size);
	free(p);
}
void operator delete [](void* p, unsigned int size) {
	(void) (size);
	free(p);
}
