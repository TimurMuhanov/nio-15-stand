/**	@defgroup	ENCODER
	@author		Zaripov Kamil
				Inertial Measurement Unit
	@{ */
	
#ifndef ENCODER_H
#define ENCODER_H


#include "ch.h"
#include "math.h"
#include "thread.h"
#include "ls7366.h"
#include "imu.h"        // for data types
#include "Terminal.h"


#define ENCODER_PERIOD_MS			2
#define ENCODER_NUMBER				9

// PPR = pulses per revolution
#define ENCODER_1_PPR				5000
#define ENCODER_2_PPR				5000
#define ENCODER_3_PPR				5000
#define ENCODER_4_PPR				3600
#define ENCODER_5_PPR				3600
#define ENCODER_6_PPR				3600
#define ENCODER_7_PPR				3600
#define ENCODER_8_PPR				3600
#define ENCODER_9_PPR				3600

#define TETHA						0
#define GAMMA						1
#define PSI							2

//#define ENCODER_PULSES_TO_ANGLE(p,ppr,offset)		(fmod(2*M_PI+((p)/(float)(ppr)*2*M_PI), 2*M_PI)- M_PI + (offset))

/// converts encoder pulses to real angle in deg
#define ENCODER_PULSES_TO_ANGLE(p,ppr,offset)		((ppr)>0 ? \
                                                            ( ((p)>(ppr)/2) ? -(360*(1-(p)/(float)(ppr))) : (360*(p)/(float)(ppr)) ) : \
                                                            ( ((p)<-(ppr)/2) ? (360*(1+(p)/(float)(ppr))) : (360*(p)/(float)(ppr)) ) \
                                                        )




#ifdef __cplusplus
extern "C" {
#endif


	void encoderInit(void);

	/**	get encoder value
		@param		id					encoder id form 0 to ENCODER_NUMBER-1
		@retval		structure with encoder data in deg */
	scalarData encoderGet(u32 id);
        void       encoderFix();
        void        encoderSetOffset(u32 id, float offset);

#ifdef __cplusplus
}
#endif



#endif

/** @} */
