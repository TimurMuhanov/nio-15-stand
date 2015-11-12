/**	@defgroup	GCS
	@author		Zaripov Kamil
				Communicate with Ground Control Station
	@{ */

#ifndef GCS_H
#define GCS_H




#define MAVLINK_DEFAULT_COMM		MAVLINK_COMM_0




#include "ch.h"
#include "hal.h"

#include "io.h"
#include "control.h"
#include "imu.h"
#include "encoder.h"
#include "servo.h"


#include "mavlink_bridge_header.h"
#include "mavlink.h"


/**	init module */
void gcsInit(void);

#endif

/** @} */
