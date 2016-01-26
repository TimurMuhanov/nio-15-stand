/**	@defgroup	ADIS16488
	@author		Zaripov Kamil
				Driver for ADIS16488 sensor
	@{ */

#ifndef ADIS16488_H
#define ADIS16488_H





#include "ch.h"
#include "hal.h"


#define	ADIS16488_NAME			"ADIS16488"
//#define	ADIS16488_DEBUG						// uncomment for enable debug, comment for disable
//#define	ADIS16488_SOFT_RESET				// comment for for soft reset, comment for HARD reset
#define	ADIS16488_UPDATE_PERIOD		20			// data update period in ms


/**	init ADIS16488 - set default counfiguration */
void adis16488Init(void);


#endif

/** @} */
