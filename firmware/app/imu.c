#include "imu.h"
#include "adis16488.h"


struct {
	float	   q[4];

	vectorData g;			// in g
	vectorData a;			// rad/s
	vectorData m;			// tesla
	scalarData p;
	scalarData T;
} imu;
binary_semaphore_t gyroDataAccess;
binary_semaphore_t accelDataAccess;
binary_semaphore_t magDataAccess;
binary_semaphore_t pressureDataAccess;
binary_semaphore_t tempDataAccess;


void imuInit(void) {
	chBSemObjectInit(&gyroDataAccess, false);
	chBSemObjectInit(&accelDataAccess, false);
	chBSemObjectInit(&magDataAccess, false);
	chBSemObjectInit(&pressureDataAccess, false);
	chBSemObjectInit(&tempDataAccess, false);

	adis16488Init();
}


vectorData imuGyroGet(void) {
	chBSemWait(&gyroDataAccess);
	vectorData ret = imu.g;
	chBSemSignal(&gyroDataAccess);
	return ret;
}
void imuGyroSet(vectorData data) {
	chBSemWait(&gyroDataAccess);
	imu.g = data;
	chBSemSignal(&gyroDataAccess);
}


vectorData imuAccelGet(void) {
	chBSemWait(&accelDataAccess);
	vectorData ret = imu.a;
	chBSemSignal(&accelDataAccess);
	return ret;
}
void imuAccelSet(vectorData data) {
	chBSemWait(&accelDataAccess);
	imu.a = data;
	chBSemSignal(&accelDataAccess);
}


vectorData imuMagGet(void) {
	chBSemWait(&magDataAccess);
	vectorData ret = imu.m;
	chBSemSignal(&magDataAccess);
	return ret;
}
void imuMagSet(vectorData data) {
	chBSemWait(&magDataAccess);
	imu.m = data;
	chBSemSignal(&magDataAccess);
}


scalarData imuPressureGet(void) {
	chBSemWait(&pressureDataAccess);
	scalarData ret = imu.p;
	chBSemSignal(&pressureDataAccess);
	return ret;
}
void imuPressureSet(scalarData data) {
	chBSemWait(&pressureDataAccess);
	imu.p = data;
	chBSemSignal(&pressureDataAccess);
}


scalarData imuTempGet(void) {
	chBSemWait(&tempDataAccess);
	scalarData ret = imu.T;
	chBSemSignal(&tempDataAccess);
	return ret;
}
void imuTempSet(scalarData data) {
	chBSemWait(&tempDataAccess);
	imu.T = data;
	chBSemSignal(&tempDataAccess);
}
