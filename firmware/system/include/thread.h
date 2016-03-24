/**	@defgroup	CONNECTION
	@author		Zaripov Kamil
                API for threading
	@{ */

#ifndef THREAD_H
#define THREAD_H

#ifdef __cplusplus

#include "ch.h"
#include "chdynamic.h"
#include "hal.h"
#include "io.h"
#include <string>
#include <map>

using namespace std;

class Signal {
    public:
                        Signal();
                       ~Signal();

        void            connect();
        void            emit();
};

class Object {
    public:
                        Object();
                       ~Object();
        void            test1(void*);
        static void     test2(void*);
};

class Thread {
    public:
        static void                     addThread( thread_t* ptr, string name );

//        template<typename T>
//        static void                     add( tt& function, T &object ) {
//            (object.function)();
//        }

        static void                     add( void (Object::*function)(void*), Object &object ) {
//            chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(256), NORMALPRIO, (object.*function), NULL);
        }
        static void                     add( void (*function)(void*) ){
            chThdCreateFromHeap(NULL,          /* NULL = Default heap. */
                                THD_WORKING_AREA_SIZE(256), /* Stack.   */
                                NORMALPRIO,    /* Initial priority.    */
                                function,      /* Thread function.     */
                                NULL);         /* Thread parameter.    */
        }
        static void                     loop();
};

#endif

#endif

/** @} */
