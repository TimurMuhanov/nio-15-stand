#include "flash.h"
#include "usbcfg.h"
#include "chprintf.h"


#define FLASH_KEY1 ((u32)0x45670123)
#define FLASH_KEY2 ((u32)0xCDEF89AB)


bool	flashIsLocked(void) {
	if( FLASH->CR & FLASH_CR_LOCK )
		return true;
	else
		return false;
}

void	flashLock(void) {
	FLASH->CR |= FLASH_CR_LOCK;
}

void	flashUnlock(void) {
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
}

void	flashEraseFirmware( void ) {
	//print("flashEraseFirmware %u:%u\n\r", BOARD_ADDRESS_TO_SECTOR(BOARD_FLASH_FIRMWARE), BOARD_ADDRESS_TO_SECTOR(BOARD_FLASH_FIRMWARE+BOARD_FLASH_FIRMWARE_SIZE) );

	FLASH->CR |= FLASH_CR_SER;

	u8 i;
	for(i = BOARD_ADDRESS_TO_SECTOR(BOARD_FLASH_FIRMWARE); i<= BOARD_ADDRESS_TO_SECTOR(BOARD_FLASH_FIRMWARE+BOARD_FLASH_FIRMWARE_SIZE); i++) {
		while( FLASH->SR & FLASH_SR_BSY );
		//print("flashEraseFirmware %u...\n\r", i);
		FLASH->CR &= ~FLASH_CR_SNB;
		FLASH->CR |= (i << 3) & 0x78;
		FLASH->CR |= FLASH_CR_SER;
		FLASH->CR |= FLASH_CR_STRT;

		chThdSleepMilliseconds(1);

		//print("flashEraseFirmware %u erased\n\r", i);
	}
	FLASH->CR &= ~FLASH_CR_SER;
}

void flashWrite( u32 beginAddress, u32* buffer, u32 len ) {
	FLASH->CR |= FLASH_CR_PG;

	FLASH->CR &= ~FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE_1;

	u32 i;
	for( i=0; i<len; i++ ) {
		while( FLASH->SR & FLASH_SR_BSY );
		*(__IO u32*)(beginAddress+i*4) = buffer[i];
	}

	FLASH->CR &= ~(FLASH_CR_PG);
}
