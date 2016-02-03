/**	@defgroup	CONNECTION
	@author		Zaripov Kamil
                API for threading
	@{ */

#ifndef THREAD_H
#define THREAD_H

#ifdef __cplusplus

#include "ch.h"
#include "hal.h"
#include "io.h"
#include "connection.h"
#include <string>
#include <map>

using namespace std;

class Thread {
    public:
        static void                     addThread( thread_t* ptr, string name );
        static void                     loop();
    private:
        static std::map<thread_t*, string>   _threads;
};

#endif

#endif

/** @} */
