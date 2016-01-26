/**	@defgroup	IMU
	@author		Zaripov Kamil
				Inertial Measurement Unit
	@{ */
	
#ifndef IMU_H
#define IMU_H


#include "ch.h"


typedef struct {
	float x;
	float y;
	float z;
	u32 time;			// us
} vectorData;

typedef struct {
	float val;
	u32 time;			// us
} scalarData;

#ifdef __cplusplus
extern "C" {
#endif


	void imuInit(void);

	// in deg
	vectorData imuGyroGet(void);
	void imuGyroSet(vectorData);

	vectorData imuAccelGet(void);
	void imuAccelSet(vectorData);

	vectorData imuMagGet(void);
	void imuMagSet(vectorData);

	scalarData imuPressureGet(void);
	void imuPressureSet(scalarData);

	scalarData imuTempGet(void);
	void imuTempSet(scalarData);


#ifdef __cplusplus
}
#endif

#endif

/** @} */
