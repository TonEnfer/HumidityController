/*
 * RTC.h
 *
 *  Created on: 5 февр. 2018 г.
 *      Author: anton.samoylov
 */

#ifndef RTC_H_
#define RTC_H_
//#include <time.h>
namespace HAL {
//typedef struct {
//	unsigned int ms : 16;
//	char s : 6;
//	char m : 6;
//	char h : 5;
//} time_t;
class RTC_class {
public:
	//time_t time;
	RTC_class();

};
extern RTC_class RTC;
} /* namespace HAL */

#endif /* RTC_H_ */
