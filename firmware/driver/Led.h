/**	@defgroup	LED
	@author		Zaripov Kamil
	@brief		Led switch on/off functions
	@{ */

#ifndef LED_H
#define LED_H





#include "ch.h"
#include "hal.h"




#define LED1_ID			0
#define LED2_ID			1



/**	switch on led
	@param		ledID		led id:
		@arg	LED1_ID		status led #1
		@arg	LED2_ID		status led #2 */
void ledOn(u8 ledID);

/**	switch off led
	@param		ledID		led id:
		@arg	LED1_ID		status led #1
		@arg	LED2_ID		status led #2 */
void ledOff(u8 ledID);


/**	toggle led
	@param		ledID		led id:
		@arg	LED1_ID		status led #1
		@arg	LED2_ID		status led #2 */
void ledToggle(u8 ledID);



#endif

/** @} */
