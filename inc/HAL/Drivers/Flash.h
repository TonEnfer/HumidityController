/*
 * Flash.h
 *
 *  Created on: 10 ����. 2018 �.
 *      Author: anton.samoylov
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <sys/_stdint.h>

namespace HAL {

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0800FFFF))

#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)

#define FLASH_FLAG_BSY                 FLASH_SR_BSY     /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR               FLASH_SR_PGERR   /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPERR  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                 FLASH_SR_EOP     /*!< FLASH End of Programming flag */

typedef enum {
	FLASH_BUSY = 1,
	FLASH_ERROR_WRP,
	FLASH_ERROR_PROGRAM,
	FLASH_COMPLETE,
	FLASH_TIMEOUT
} FLASH_Status;

class Flash_class {
protected:
	FLASH_Status waitForLastOperation(uint32_t Timeout);
	FLASH_Status getStatus(void);
public:
	Flash_class();
	void unlock(void);
	void lock(void);

	FLASH_Status erasePage(uint32_t Page_Address);
	FLASH_Status programHalfWord(uint32_t Address, uint16_t Data);

};
extern Flash_class Flash;
} /* namespace HAL */

#endif /* FLASH_H_ */
