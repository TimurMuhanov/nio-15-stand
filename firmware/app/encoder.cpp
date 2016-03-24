#include "encoder.h"


static thread_t* updateThread;
static THD_FUNCTION(encoderUpdate, arg);
static THD_WORKING_AREA(encoderUpdateWorkingArea, 1024);
scalarData encoder[ENCODER_NUMBER];
float encoderOffset[ENCODER_NUMBER];
static binary_semaphore_t dataAccess;



THD_FUNCTION(encoderUpdate, arg) {
    int i;
    for( i=0; i<ENCODER_NUMBER; i++) {
        encoder[i].time = ST2US(chVTGetSystemTime());
        encoder[i].val = 0;
        ls7366Init(i+1);
    }

	systime_t chibios_time = chVTGetSystemTime();

    while( !chThdShouldTerminateX() ) {
		chibios_time += MS2ST(ENCODER_PERIOD_MS);

		chBSemWait(&dataAccess);
		u32 time = ls7366Fix();

		encoder[0].time = encoder[1].time = encoder[2].time = encoder[3].time = encoder[4].time =
		encoder[5].time = encoder[6].time = encoder[7].time = encoder[8].time = time;

		encoder[0].val =-ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(1), ENCODER_1_PPR, encoderOffset[0]);
		encoder[1].val =-ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(2), ENCODER_2_PPR, encoderOffset[1]);
		encoder[2].val =-ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(3), ENCODER_3_PPR, encoderOffset[2]);
		encoder[3].val = ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(4), ENCODER_4_PPR, encoderOffset[3]);
		encoder[4].val = ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(5), ENCODER_5_PPR, encoderOffset[4]);
		encoder[5].val = ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(6), ENCODER_6_PPR, encoderOffset[5]);
		encoder[6].val = ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(7), ENCODER_7_PPR, encoderOffset[6]);
		encoder[7].val = ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(8), ENCODER_8_PPR, encoderOffset[7]);
		encoder[8].val = ENCODER_PULSES_TO_ANGLE( ls7366ReadCounter(9), ENCODER_9_PPR, encoderOffset[8]);

		chBSemSignal(&dataAccess);

		//print("encoder %u %f %f %f\n\r", encoder[0].time, encoder[0].val, encoder[1].val, encoder[2].val);

		chThdSleepUntil(chibios_time);
    }
    chThdExit( 0 );
}


void encoderInit(void) {
	chBSemObjectInit(&dataAccess, false);

	/*encoderOffset[0] = paramGet(PARAM_ENCODER1_OFFSET);
	encoderOffset[1] = paramGet(PARAM_ENCODER2_OFFSET);
	encoderOffset[2] = paramGet(PARAM_ENCODER3_OFFSET);
	encoderOffset[3] = paramGet(PARAM_ENCODER4_OFFSET);
	encoderOffset[4] = paramGet(PARAM_ENCODER5_OFFSET);
	encoderOffset[5] = paramGet(PARAM_ENCODER6_OFFSET);
	encoderOffset[6] = paramGet(PARAM_ENCODER7_OFFSET);
	encoderOffset[7] = paramGet(PARAM_ENCODER8_OFFSET);
	encoderOffset[8] = paramGet(PARAM_ENCODER9_OFFSET);*/

    updateThread = chThdCreateStatic(   encoderUpdateWorkingArea,
                                        sizeof(encoderUpdateWorkingArea),
                                        NORMALPRIO, encoderUpdate, NULL);
    Thread::addThread( updateThread, string("enc") );
}


scalarData encoderGet(u32 id) {
	scalarData ret = {0,0};

	if(id > ENCODER_NUMBER-1)
		return ret;

	chBSemWait(&dataAccess);
	ret.time = encoder[id].time;
	ret.val = encoder[id].val;
	chBSemSignal(&dataAccess);
	return ret;
}
