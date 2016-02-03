/**	@defgroup	CONTROL
	@author		Zaripov Kamil
				Board control
	@{ */
	
#ifndef CONTROL_H
#define CONTROL_H


#include "ch.h"
#include "thread.h"
#include "servo.h"


#define	CONTROL_CONNECTED			1
#define	CONTROL_DISCONNECTED		0

#define	CONTROL_MODE_RUN			1

#define	CONTROL_USER_CODE_UPDATE	20


#ifdef __cplusplus
extern "C" {
#endif


	void controlInit( void );

	u32 controlStatus( void );

	void controlStart( void );

	void controlStop( void );


#ifdef __cplusplus
}
#endif



#endif

/** @} */
