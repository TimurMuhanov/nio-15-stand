#include "imu.h"
#include "adis16488.h"
#include "thread.h"


struct {
	float	   q[4];

	vectorData g;			// in g
	vectorData a;			// rad/s
	vectorData m;			// tesla
	scalarData p;
	scalarData T;
} imu;
binary_semaphore_t dataAccess;
static thread_t* updateThread;
static THD_FUNCTION(update, arg);
static THD_WORKING_AREA(updateWorkingArea, 1024);

THD_FUNCTION(update, arg) {

    adis16488Init();

    systime_t chibios_time = chVTGetSystemTime();

    while( !chThdShouldTerminateX() ) {
//        chibios_time += MS2ST(IMU_UPDATE_PERIOD);

        adis16488Update();

//        chThdSleepUntil(chibios_time);
        chThdSleepMilliseconds(IMU_UPDATE_PERIOD);
    }

    chThdExit( 0 );
}


void imuInit(void) {
    chBSemObjectInit(&dataAccess, false);

    updateThread = chThdCreateStatic(   updateWorkingArea,
                                        sizeof(updateWorkingArea),
                                        NORMALPRIO, update, NULL);
    Thread::addThread( updateThread, string("imu") );
}


vectorData imuGyroGet(void) {
    chBSemWait(&dataAccess);
	vectorData ret = imu.g;
    chBSemSignal(&dataAccess);
	return ret;
}
void imuGyroSet(vectorData data) {
    chBSemWait(&dataAccess);
	imu.g = data;
    chBSemSignal(&dataAccess);
}


vectorData imuAccelGet(void) {
    chBSemWait(&dataAccess);
	vectorData ret = imu.a;
    chBSemSignal(&dataAccess);
	return ret;
}
void imuAccelSet(vectorData data) {
    chBSemWait(&dataAccess);
	imu.a = data;
    chBSemSignal(&dataAccess);
}


vectorData imuMagGet(void) {
    chBSemWait(&dataAccess);
	vectorData ret = imu.m;
    chBSemSignal(&dataAccess);
	return ret;
}
void imuMagSet(vectorData data) {
    chBSemWait(&dataAccess);
	imu.m = data;
    chBSemSignal(&dataAccess);
}


scalarData imuPressureGet(void) {
    chBSemWait(&dataAccess);
	scalarData ret = imu.p;
    chBSemSignal(&dataAccess);
	return ret;
}
void imuPressureSet(scalarData data) {
    chBSemWait(&dataAccess);
	imu.p = data;
    chBSemSignal(&dataAccess);
}


scalarData imuTempGet(void) {
    chBSemWait(&dataAccess);
	scalarData ret = imu.T;
    chBSemSignal(&dataAccess);
	return ret;
}
void imuTempSet(scalarData data) {
    chBSemWait(&dataAccess);
	imu.T = data;
    chBSemSignal(&dataAccess);
}
