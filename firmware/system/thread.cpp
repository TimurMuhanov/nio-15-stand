#include "thread.h"

std::map<thread_t*, string> Thread::_threads;

void Thread::addThread(thread_t* ptr, string name) {
    _threads[ptr] = name;
}

void Thread::loop() {
    u32 lastTime = 0;

    while(1) {
        palTogglePad(GPIOC, 15);
        chThdSleepMilliseconds(1000);

        /*u32 time = 0;
        u32 tCount = 0;
        thread_t *tp = chRegFirstThread();
//        print( "id\t\t\ttime\n\r" );
        do {
            if( tp == chSysGetIdleThreadX() )
                tp = chRegNextThread(tp);
            u32 tTime = chThdGetTicksX(tp);
            time += tTime;
            ++tCount;
            if( _threads.find(tp) != _threads.end() )
                print( "0x%8X\t%s\t%u\n\r", tp, _threads[tp].c_str(), tTime );
            else
                print( "0x%8X\t\t\t%u\n\r", tp, tTime );
            tp = chRegNextThread(tp);
        } while (tp != NULL);

        print( "%u|%u, %u\n\r", (time - lastTime), ST2MS(time-lastTime), chVTGetSystemTime() );
        connectionSetCpuInfo( (float) ST2MS(time-lastTime)/1000, ST2MS(time-lastTime), chVTGetSystemTime(), tCount );

        lastTime = time;*/
    }
}
