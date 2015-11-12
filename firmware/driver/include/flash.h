/**	@defgroup	FLASH
	@brief		Function to use internal flash
	@{ */

#ifndef FLASH_H
#define FLASH_H

#include "ch.h"
#include "hal.h"


void 	flashLock( void );

void	flashUnlock( void );

/** erase firmware */
void	flashEraseFirmware( void );

/** write 32bit word to flash */
void	flashWrite( u32 beginAddress, u32* buffer, u32 len );


#endif

/** @} */
