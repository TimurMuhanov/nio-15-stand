/**	@defgroup	CONNECTION
	@author		Zaripov Kamil
                API for threading
	@{ */

#ifndef THREAD_H
#define THREAD_H

#include "ch.hpp"
#include "chdynamic.h"
#include "hal.h"
#include <string>
#include <map>

using namespace std;

class Thread {
    public:
        static void                     loop();
};

#endif

/** @} */
