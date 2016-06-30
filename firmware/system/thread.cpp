#include "Thread.h"
#include "Terminal.h"
#include "Connection.h"
#include <cstring>


void Thread::loop() {
    u32 lastTime = 0;

    systime_t nextTime = chVTGetSystemTime();
    std::map<thread_t*,u32> lastTicks;
    while(1) {
        palTogglePad(GPIOC, 15);
        nextTime += MS2ST(1000);

        u32 time = 0;
        u32 count = 0;
        thread_t *thread = chRegFirstThread();
        do {
            if( thread == chSysGetIdleThreadX() )
                thread = chRegNextThread(thread);
            u32 ticks = chThdGetTicksX(thread);
            time += ticks;
            ++count;
//            print( "0x%8X\t%s\t%u\n\r", thread, chRegGetThreadNameX(thread), ST2MS(ticks - lastTicks[thread]) );
            lastTicks[thread] = ticks;
            thread = chRegNextThread(thread);
        } while( thread != NULL );

//        Terminal::print( "%u|%u, %u\n\r", (time - lastTime), ST2MS(time-lastTime), chVTGetSystemTime() );
        Connection::instance().setCpuInfo( (float) (time-lastTime)/MS2ST(1000), ST2MS(chVTGetSystemTime()), count );


        lastTime = time;

        chThdSleepUntil(nextTime);
    }
}
