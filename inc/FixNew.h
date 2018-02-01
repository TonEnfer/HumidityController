/*
 * FixNew.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef FIXNEW_H_
#define FIXNEW_H_

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



#endif /* FIXNEW_H_ */
