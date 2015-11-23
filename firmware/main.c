#include "ch.h"
#include "hal.h"

#include "system.h"
#include "driver.h"
#include "app.h"

int main(void) {
	halInit();
	chSysInit();

	ioInit();
	parameterInit();

	Parameter* param1 = parameterGet( "param1" );
	param1->val.Int = 2;
	parameterSync();

	imuInit();
	encoderInit();
	servoInit();
	servoPower(TRUE);

	//gcsInit();
	//controlInit();

	palSetPadMode(GPIOC, 15, PAL_MODE_OUTPUT_PUSHPULL);

	while(1) {
		palTogglePad(GPIOC, 15);
		chThdSleepMilliseconds(500);
		//print("as");
	}
}
