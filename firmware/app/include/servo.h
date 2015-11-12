/**	@defgroup	SERVO
	@author		Zaripov Kamil
				Driver for control servos using PWM
	@{ */

#ifndef SERVO_H
#define SERVO_H


#include "ch.h"
#include "hal.h"
#include "imu.h"
#include "parameter.h"


#define SERVO_UPDATE_PERIOD_MS			50
#define SERVO_NUMBER					8
//#define SERVO_PERCENT_TO_PWM(x)			((u32)(800+(float)14*(x)))
#define SERVO_ANGLE_TO_PWM(a,p1,p2,p3)		( (a) > 0.0 ? \
											( (p2) + (a)/20.0f*((p3)-(p2)) ) : \
											( (p2) + (a)/20.0f*((p2)-(p1)) ) )


/**	init servo */
void servoInit(void);


/**	enable/disable power
	@param		state					power status to set
		@arg	TRUE					enable power
		@arg	FALSE					disable power */
void servoPower(u8 state);


/**	get trust
	@param		id						servo id in form 0 to SERVO_NUMBER-1
	@retval		strucure with servo data, where .time is time in microsec and .val is angle in deg */
scalarData servoGet(u32 id);


/**	set trust
	@param		id						servo id in form 0 to SERVO_NUMBER-1
	@param		angle					angle in deg */
void servoSet(u32 id, float angle);


#endif

/** @} */
