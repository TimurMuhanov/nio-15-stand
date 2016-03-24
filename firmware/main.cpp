#include "ch.h"
#include "hal.h"

#include "system.h"
#include "driver.h"
#include "app.h"

int main(void) {
	halInit();
	chSysInit();

    ioInit();
    FileSystem::init();
    Settings::init();
    Log::init();

    imuInit();
    navInit();
    encoderInit();
    servoInit();
    servoPower(TRUE);

    connectionInit();
    controlInit();

    Thread::loop();
}
