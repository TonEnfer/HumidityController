/*
 * Flash.cpp
 *
 *  Created on: 10 ����. 2018 �.
 *      Author: anton.samoylov
 */

#include <HAL/Drivers/Flash.h>
#include <stm32f0xx.h>

namespace HAL {
Flash_class::Flash_class() {
}

void Flash_class::unlock() {
	if ((FLASH->CR & FLASH_CR_LOCK) != RESET) {
		/* Unlocking the program memory access */
		FLASH->KEYR = FLASH_FKEY1;
		FLASH->KEYR = FLASH_FKEY2;
	}
}

void Flash_class::lock() {
	FLASH->CR |= FLASH_CR_LOCK;
}

FLASH_Status Flash_class::erasePage(uint32_t Page_Address) {
	FLASH_Status status = FLASH_COMPLETE;
	//assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));
	status = waitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	if (status == FLASH_COMPLETE) {
		/* If the previous operation is completed, proceed to erase the page */
		FLASH->CR |= FLASH_CR_PER;
		FLASH->AR = Page_Address;
		FLASH->CR |= FLASH_CR_STRT;

		/* Wait for last operation to be completed */
		status = waitForLastOperation(FLASH_ER_PRG_TIMEOUT);

		/* Disable the PER Bit */
		FLASH->CR &= ~FLASH_CR_PER;
	}
	return status;
}
FLASH_Status Flash_class::programHalfWord(uint32_t Address, uint16_t Data) {
	FLASH_Status status = FLASH_COMPLETE;
	status = waitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	if (status == FLASH_COMPLETE) {
		/* If the previous operation is completed, proceed to program the new data */
		FLASH->CR |= FLASH_CR_PG;

		*(__IO uint16_t*) Address = Data;

		/* Wait for last operation to be completed */
		status = waitForLastOperation(FLASH_ER_PRG_TIMEOUT);

		/* Disable the PG Bit */
		FLASH->CR &= ~FLASH_CR_PG;
	}

	/* Return the Program Status */
	return status;
}

FLASH_Status Flash_class::waitForLastOperation(uint32_t Timeout) {
	FLASH_Status status = FLASH_COMPLETE;

	/* Check for the FLASH Status */
	status = getStatus();

	/* Wait for a FLASH operation to complete or a TIMEOUT to occur */
	while ((status == FLASH_BUSY) && (Timeout != 0x00)) {
		status = getStatus();
		Timeout--;
	}

	if (Timeout == 0x00) {
		status = FLASH_TIMEOUT;
	}
	/* Return the operation status */
	return status;
}

FLASH_Status Flash_class::getStatus(void) {
	FLASH_Status FLASHstatus = FLASH_COMPLETE;

	if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) {
		FLASHstatus = FLASH_BUSY;
	} else {
		if ((FLASH->SR & (uint32_t) FLASH_FLAG_WRPERR) != (uint32_t) 0x00) {
			FLASHstatus = FLASH_ERROR_WRP;
		} else {
			if ((FLASH->SR & (uint32_t) (FLASH_SR_PGERR)) != (uint32_t) 0x00) {
				FLASHstatus = FLASH_ERROR_PROGRAM;
			} else {
				FLASHstatus = FLASH_COMPLETE;
			}
		}
	}
	/* Return the FLASH Status */
	return FLASHstatus;
}

Flash_class Flash = Flash_class();
} /* namespace HAL */
