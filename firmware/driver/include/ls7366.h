/**	@defgroup	LS7366
	@author		Zaripov Kamil
				Driver for quadrature counter LS7366 (LS7366-S, LS7366-TS)
	@{ */

#ifndef LS7366_H
#define LS7366_H


#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**	init LS7366 - set default configuration
        @param		number					encoder number */
    void ls7366Init(u8 encoderNumber);

    /**	fix counter value (load CNTR to OTR)
        @retval		fixed time in microseconds from system start */
    u32 ls7366Fix(void);

    /**	read OTR value
        @todo		check value sign
        @param		encoderNumber			serial number of encoder
        @retval		counter value */
    s32 ls7366ReadCounter(u8 encoderNumber);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
