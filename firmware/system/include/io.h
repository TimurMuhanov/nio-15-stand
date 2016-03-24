/**	@defgroup	IO
	@author		Zaripov Kamil
				Contain basic Input\Ouput functions using USB and USART
				There are two channels:
				- terminal channel			it is text chennel to control system using text commands
                - telemetry channel		it is binary chennel to control system using MAVLink protocol
	@{ */

#ifndef IO_H
#define IO_H


#include "ch.hpp"
#include "hal.h"

#include "telemetry.h"
#include <stdarg.h>
//#include <iostream>
#include "chprintf.h"
#include "usbcfg.h"
#include "ff.h"


#define IO_WRITE_BUFFER			100

#ifdef __cplusplus

#include <string>
using namespace std;
using namespace chibios_rt;

/*enum class Permission {
    Read = 0x01,
    Write = 0x02
};

enum class Mode {
    OpenExisting = 0x04,    // Opens the file. The function fails if the file is not existing.
    OpenAlways = 0x08,      // Opens the file if it is existing. If not, a new file will be created.
    CreateNew = 0x10,       // Creates a new file. The function fails if the file is existing.
    CreateAlways = 0x20     // Creates a new file. If the file is existing, it will be truncated and overwritten.
};*/

class FileSystem {
    private:
                                            FileSystem();
                                           ~FileSystem();
    public:

        static void                         init();
        static bool                         isAvailable();

        static bool                         open( FIL& fil, const string& file, const u8 mode );
        static bool                         write( FIL& fil, const string& data );
        static bool                         write( FIL& fil, const u8* data, const u32 len );
        static bool                         readLine( FIL& fil, string& line );
        static bool                         sync( FIL& fil );
        static bool                         erase( FIL& fil );

    private:
        static FATFS                        _filesystem;
        static bool                         _accessibility;
        static binary_semaphore_t           _access;
};

//template< typename Type = u8 >
//class Container {
//    class Index {
//        public:
//                            Index( int index );
//                           ~Index();
//        inline Type&        operator()( int index );
//        inline Index&       operator+( int index );
//        inline Index&       operator-( int index );
//    };

//    public:
//                        Container();
//                        Container( std::initializer_list<Type> list );
//                       ~Container();

//    inline Type&        operator()( int index );
//    inline Type&        operator()( int index1, int index2 );
//};

/*
class Iterfaces {
    private:
                                            Iterfaces();
                                           ~Iterfaces();
    public:

        static void                         init();
        static std::iostream                terminal();
        static std::iostream                telemetry();
    private:
};
*/















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


#ifdef __cplusplus
}
#endif



#endif

/** @} */
