#include "thread.h"
#include "connection.h"
#include <cstring>

void Thread::addThread(thread_t* ptr, string name) {
    char * tmpName = (char*) malloc(sizeof(char*)*(name.length()+1));
    strcpy(tmpName, name.c_str());
    chRegSetThreadNameX( ptr, tmpName );
}

//template<typename T>
//void Thread::add(void (T::*function)(), T* object) {
//    (object->*function)();

////    std::bind();
//}

void Thread::loop() {
    u32 lastTime = 0;

//    chRegSetThreadName("main");

    while(1) {
        palTogglePad(GPIOC, 15);
        chThdSleepMilliseconds(1000);

//        u32 time = 0;
//        u32 tCount = 0;
//        thread_t *tp = chRegFirstThread();
////        print( "id\t\t\ttime\n\r" );
//        do {
//            if( tp == chSysGetIdleThreadX() )
//                tp = chRegNextThread(tp);
//            u32 tTime = chThdGetTicksX(tp);
//            time += tTime;
//            ++tCount;
////            print( "0x%8X\t%s\t%u\n\r", tp, chRegGetThreadNameX(tp), tTime );
//            tp = chRegNextThread(tp);
//        } while (tp != NULL);

////        print( "%u|%u, %u\n\r", (time - lastTime), ST2MS(time-lastTime), chVTGetSystemTime() );
//        connectionSetCpuInfo( (float) ST2MS(time-lastTime)/1000, ST2MS(time-lastTime), chVTGetSystemTime(), tCount );

//        lastTime = time;
    }
}

Object::Object() {

}

Object::~Object() {

}

void Object::test1(void*)
{

}

void Object::test2(void*)
{

}
