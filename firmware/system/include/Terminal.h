/**	@defgroup	Terminal
	@author		Zaripov Kamil
				Contain basic Input\Ouput functions using USB and USART
				There are two channels:
				- terminal channel			it is text chennel to control system using text commands
				- telemethry channel		it is binary chennel to control system using MAVLink protocol
	@{ */

#ifndef TERMINAL_H
#define TERMINAL_H


#include "ch.hpp"
#include "hal.h"
#include <stdarg.h>
#include "chprintf.h"
#include <cstring>
#include "usbcfg.h"


using namespace chibios_rt;


class Terminal {
        /**	init virtual com port */
                                            Terminal();
                                           ~Terminal();
    public:
        static Terminal&                    instance();

        /**	formated print to terminal channel, use it like printf from stdio.h
            @param		string		formatting string
            @param		...			list of parameters */
        static void                         print(const char* string, ...);

        /**	send package to terminal channel
            @param		buf			pointer to the package begin
            @param		len			package len in bytes */
        static u32                          send(const u8* buf, const u32 len);

        /**	receive package from terminal channel
            @param		buf			pointer to the package begin
            @param		len			package len in bytes */
        static u32                          read(u8* buf, const u32 len);

        /**	number of bytes available in terminal channel
            @retval		len			available bytes */
        static u32                          available();

        static u8                           get();
        static void                         put(u8 byte);
    private:
        Mutex                               _sendMutex;
        Mutex                               _receiveMutex;
};

#endif

/** @} */
