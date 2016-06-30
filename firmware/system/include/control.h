/**	@defgroup	CONTROL
	@author		Zaripov Kamil
				Board control
	@{ */
	
#ifndef CONTROL_H
#define CONTROL_H


#include "ch.hpp"
#include "Thread.h"
#include "servo.h"


#define	CONTROL_CONNECTED			1
#define	CONTROL_DISCONNECTED		0
#define	CONTROL_MODE_RUN			1
#define	CONTROL_USER_CODE_UPDATE	20


void    controlInit();

u32     controlStatus();

void    controlStart();

void    controlStop();


#endif

/** @} */
