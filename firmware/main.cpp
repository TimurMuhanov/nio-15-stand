#include "ch.h"
#include "hal.h"

#include "system.h"
#include "driver.h"
#include "app.h"

int main(void) {
	halInit();
	chSysInit();

    palSetPadMode(GPIOC, 15, PAL_MODE_OUTPUT_PUSHPULL);         // blue
    palClearPad(GPIOC, 15);
    palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);         // red
    palClearPad(GPIOC, 13);
    palSetPadMode(GPIOC, 0, PAL_MODE_OUTPUT_PUSHPULL);          // orange
    palClearPad(GPIOC, 0);

    palSetPadMode(GPIOC, 14, PAL_MODE_OUTPUT_PUSHPULL);         // external?
    palClearPad(GPIOC, 14);

    ioInit();
    Settings::init();
    Log::init();

//    imuInit();
    navInit();
    encoderInit();
	servoInit();
	servoPower(TRUE);

    connectionInit();
    controlInit();

    Thread::loop();
}
