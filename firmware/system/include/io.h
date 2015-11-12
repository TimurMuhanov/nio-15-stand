/**	@defgroup	IO
	@author		Zaripov Kamil
				Contain basic Input\Ouput functions using USB and USART
				There are two channels:
				- terminal channel			it is text chennel to control system using text commands
				- telemethry channel		it is binary chennel to control system using MAVLink protocol
	@{ */

#ifndef IO_H
#define IO_H





#include "ch.h"
#include "hal.h"

#include <stdarg.h>
#include "chprintf.h"
#include "usbcfg.h"
#include "ff.h"




#define IO_WRITE_BUFFER			100


#ifdef __cplusplus
extern "C" {
#endif



	/**	init virtual com port */
	void ioInit(void);


	/**	formated print to terminal channel, use it like printf from stdio.h
		@param		string		formatting string
		@param		...			list of parameters */
	void print(const char* string, ...);

	/**	send package to terminal channel
		@param		buf			pointer to the package begin
		@param		len			package len in bytes */
	void sendToTerminal(const u8* buf, const u32 len);

	/**	receive package from terminal channel
		@param		buf			pointer to the package begin
		@param		len			package len in bytes */
	void receiveFromTerminal(u8* buf, const u32 len);

	/**	number of bytes available in terminal channel
		@retval		len			available bytes */
	u32 availableFromTerminal(void);



	/**	send package to telemethry channel (non-blocking)
		@param		buf			pointer to the package begin
		@param		len			package len in bytes */
	void sendToTelemethry(const u8* buf, const u32 len);

	/**	receive package to telemethry channel (blocking)
		@param		buf			pointer to the package begin
		@param		len			package len in bytes */
	void receiveFromTelemethry(u8* buf, const u32 len);

	/**	number of bytes available in telemethry channel
		@retval		len			available bytes */
	u32 availableFromTelemethry(void);


	/**	checks sd card accessibility
		@retval		bool		sd card accessibility */
	bool sdCardInited(void);

#ifdef __cplusplus
}
#endif



#endif

/** @} */
