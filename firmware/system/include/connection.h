/**	@defgroup	CONNECTION
	@author		Zaripov Kamil
				Communicate with Ground Control Station
	@{ */

#ifndef CONNECTION_H
#define CONNECTION_H




#define MAVLINK_DEFAULT_COMM		MAVLINK_COMM_0




#include "ch.h"
#include "hal.h"

#include "thread.h"
#include "io.h"
#include "control.h"
#include "imu.h"
#include "nav.h"
#include "encoder.h"
#include "servo.h"

#include "mavlink_bridge_header.h"
#include "mavlink.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**	init module */
    void connectionInit(void);

    /**	set cpu udage
    @param      usage       cpu usage in range 0..1 */
    void connectionSetCpuInfo(float usage, u32 usageTime, u32 systemTime, u32 threadCount);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
