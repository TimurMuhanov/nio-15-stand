#include "servo.h"
#include "settings.h"

static thread_t* updateThread;
static THD_FUNCTION(servoUpdate, arg);
static THD_WORKING_AREA(servoUpdateWorkingArea, 128);
scalarData servo[SERVO_NUMBER];
mutex_t servoReadData;
static binary_semaphore_t dataAccess;

struct {
	u32			angleM20Pwm;
	u32			angle0Pwm;
	u32			angle20Pwm;
	float		minAngle;
	float		maxAngle;
} servoConfig[SERVO_NUMBER];


void servoInit(void) {
	chBSemObjectInit(&dataAccess, false);

	/*servoConfig[0].angleM20Pwm = paramGet(PARAM_SERVO1_ANGLE_M20_PWM);
	servoConfig[0].angle0Pwm = paramGet(PARAM_SERVO1_ANGLE_0_PWM);
	servoConfig[0].angle20Pwm = paramGet(PARAM_SERVO1_ANGLE_20_PWM);
	servoConfig[0].minAngle = paramGet(PARAM_SERVO1_MIN_ANGLE);
	servoConfig[0].maxAngle = paramGet(PARAM_SERVO1_MAX_ANGLE);

	servoConfig[1].angleM20Pwm = paramGet(PARAM_SERVO2_ANGLE_M20_PWM);
	servoConfig[1].angle0Pwm = paramGet(PARAM_SERVO2_ANGLE_0_PWM);
	servoConfig[1].angle20Pwm = paramGet(PARAM_SERVO2_ANGLE_20_PWM);
	servoConfig[1].minAngle = paramGet(PARAM_SERVO2_MIN_ANGLE);
	servoConfig[1].maxAngle = paramGet(PARAM_SERVO2_MAX_ANGLE);

	servoConfig[2].angleM20Pwm = paramGet(PARAM_SERVO3_ANGLE_M20_PWM);
	servoConfig[2].angle0Pwm = paramGet(PARAM_SERVO3_ANGLE_0_PWM);
	servoConfig[2].angle20Pwm = paramGet(PARAM_SERVO3_ANGLE_20_PWM);
	servoConfig[2].minAngle = paramGet(PARAM_SERVO3_MIN_ANGLE);
	servoConfig[2].maxAngle = paramGet(PARAM_SERVO3_MAX_ANGLE);

	servoConfig[3].angleM20Pwm = paramGet(PARAM_SERVO4_ANGLE_M20_PWM);
	servoConfig[3].angle0Pwm = paramGet(PARAM_SERVO4_ANGLE_0_PWM);
	servoConfig[3].angle20Pwm = paramGet(PARAM_SERVO4_ANGLE_20_PWM);
	servoConfig[3].minAngle = paramGet(PARAM_SERVO4_MIN_ANGLE);
	servoConfig[3].maxAngle = paramGet(PARAM_SERVO4_MAX_ANGLE);

	servoConfig[4].angleM20Pwm = paramGet(PARAM_SERVO5_ANGLE_M20_PWM);
	servoConfig[4].angle0Pwm = paramGet(PARAM_SERVO5_ANGLE_0_PWM);
	servoConfig[4].angle20Pwm = paramGet(PARAM_SERVO5_ANGLE_20_PWM);
	servoConfig[4].minAngle = paramGet(PARAM_SERVO5_MIN_ANGLE);
	servoConfig[4].maxAngle = paramGet(PARAM_SERVO5_MAX_ANGLE);

	servoConfig[5].angleM20Pwm = paramGet(PARAM_SERVO6_ANGLE_M20_PWM);
	servoConfig[5].angle0Pwm = paramGet(PARAM_SERVO6_ANGLE_0_PWM);
	servoConfig[5].angle20Pwm = paramGet(PARAM_SERVO6_ANGLE_20_PWM);
	servoConfig[5].minAngle = paramGet(PARAM_SERVO6_MIN_ANGLE);
	servoConfig[5].maxAngle = paramGet(PARAM_SERVO6_MAX_ANGLE);

	servoConfig[6].angleM20Pwm = paramGet(PARAM_SERVO7_ANGLE_M20_PWM);
	servoConfig[6].angle0Pwm = paramGet(PARAM_SERVO7_ANGLE_0_PWM);
	servoConfig[6].angle20Pwm = paramGet(PARAM_SERVO7_ANGLE_20_PWM);
	servoConfig[6].minAngle = paramGet(PARAM_SERVO7_MIN_ANGLE);
	servoConfig[6].maxAngle = paramGet(PARAM_SERVO7_MAX_ANGLE);

	servoConfig[7].angleM20Pwm = paramGet(PARAM_SERVO8_ANGLE_M20_PWM);
	servoConfig[7].angle0Pwm = paramGet(PARAM_SERVO8_ANGLE_0_PWM);
	servoConfig[7].angle20Pwm = paramGet(PARAM_SERVO8_ANGLE_20_PWM);
	servoConfig[7].minAngle = paramGet(PARAM_SERVO8_MIN_ANGLE);
	servoConfig[7].maxAngle = paramGet(PARAM_SERVO8_MAX_ANGLE);*/

	int i;
    for( i=0; i<SERVO_NUMBER; i++)
        servoSet(i, 0);

    updateThread = chThdCreateStatic(   servoUpdateWorkingArea,
                                        sizeof(servoUpdateWorkingArea),
                                        NORMALPRIO, servoUpdate, NULL);
}

void servoPower(u8 state) {
	if(state == TRUE) {
		palClearPad(BOARD_PWM_ENABLE_PORT, BOARD_PWM_ENABLE_PIN);
	} else {
		palSetPad(BOARD_PWM_ENABLE_PORT, BOARD_PWM_ENABLE_PIN);
	}
}

scalarData servoGet(u32 id) {
	scalarData ret = {0,0};

	if(id > SERVO_NUMBER-1)
		return ret;

	chBSemWait(&dataAccess);
	ret.time = servo[id].time;
	ret.val = servo[id].val;
	chBSemSignal(&dataAccess);
	return ret;
}

void servoSet(u32 id, float angle) {
	if(id >= SERVO_NUMBER-1)
		return;

	if( angle > servoConfig[id].maxAngle || angle < servoConfig[id].minAngle )
		return;

	chBSemWait(&dataAccess);
	//servo[id].time = ST2MS(chVTGetSystemTime());
	servo[id].val = angle;
	chBSemSignal(&dataAccess);

	s32 pwm = SERVO_ANGLE_TO_PWM(angle, (float)servoConfig[id].angleM20Pwm, (float)servoConfig[id].angle0Pwm, (float)servoConfig[id].angle20Pwm);
	switch(id+1) {
		case 1:		// PA3
			pwmEnableChannel(&BOARD_PWM_DEVICE1, 3, pwm);
			break;
		case 2:		// PB0
			pwmEnableChannel(&BOARD_PWM_DEVICE2, 2, pwm);
			break;
		case 3:		// PB1
			pwmEnableChannel(&BOARD_PWM_DEVICE2, 3, pwm);
			break;
		case 4:		// PC6
			pwmEnableChannel(&BOARD_PWM_DEVICE2, 0, pwm);
			break;
		case 5:		// PC7
			pwmEnableChannel(&BOARD_PWM_DEVICE2, 1, pwm);
			break;
		case 6:		// PA2
			pwmEnableChannel(&BOARD_PWM_DEVICE1, 2, pwm);
			break;
		case 7:		// PA1
			pwmEnableChannel(&BOARD_PWM_DEVICE1, 1, pwm);
			break;
		case 8:		// PA0
			pwmEnableChannel(&BOARD_PWM_DEVICE1, 0, pwm);
			break;
	}
}


THD_FUNCTION(servoUpdate, arg) {
	systime_t chibios_time = chVTGetSystemTime();

	while(1) {
		chibios_time += MS2ST(SERVO_UPDATE_PERIOD_MS);

		chBSemWait(&dataAccess);
		int i;
		for( i=0; i<SERVO_NUMBER; i++)
			servo[i].time = chVTGetSystemTime();
		chBSemSignal(&dataAccess);

		chThdSleepUntil(chibios_time);
    }
}
