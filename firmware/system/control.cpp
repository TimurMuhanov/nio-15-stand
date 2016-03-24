#include "control.h"


static u32 status;
thread_t* userCodeThread;
static THD_FUNCTION(userCodeUpdate, arg);
static THD_WORKING_AREA(userCodeUpdateWorkingArea, 1024);
extern "C" void process( void );
extern "C" void processInit( void );


void controlInit() {
	status = 0;
}


u32 controlStatus() {
	return status;
}

void controlStart() {
	if( status & CONTROL_MODE_RUN )
		return;

	status |= CONTROL_MODE_RUN;

	processInit();
    userCodeThread = chThdCreateStatic( userCodeUpdateWorkingArea,
                                        sizeof(userCodeUpdateWorkingArea),
                                        NORMALPRIO, userCodeUpdate, NULL);
    Thread::addThread( userCodeThread, string("control") );

}

void controlStop() {
	if( !(status & CONTROL_MODE_RUN) )
		return;

	status &= ~(u32)CONTROL_MODE_RUN;

	chThdTerminate(userCodeThread);
}


THD_FUNCTION(userCodeUpdate, arg) {
	systime_t time = chVTGetSystemTime();

    while( !chThdShouldTerminateX() ) {
		time += MS2ST(CONTROL_USER_CODE_UPDATE);

		process();

		chThdSleepUntil(time);
    }
    chThdExit( 0 );
}
