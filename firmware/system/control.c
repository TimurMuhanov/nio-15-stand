#include "control.h"


static u32 status;
thread_t* userCodeThread;
msg_t userCodeUpdate(void* var);
extern void process( void );
extern void processInit( void );


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
	userCodeThread = chThdCreateFromHeap(	NULL,
								THD_WORKING_AREA_SIZE(256),
								NORMALPRIO,
								userCodeUpdate,
								NULL );
}

void controlStop() {
	if( !(status & CONTROL_MODE_RUN) )
		return;

	status &= ~(u32)CONTROL_MODE_RUN;

	chThdTerminate(userCodeThread);
}


msg_t userCodeUpdate(void* var) {
	systime_t time = chVTGetSystemTime();

	while (1) {
		time += MS2ST(CONTROL_USER_CODE_UPDATE);

		process();

		chThdSleepUntil(time);

		if( chThdShouldTerminateX() ) {
			chThdExit( 0 );
		}
	}
	return 0;
}
