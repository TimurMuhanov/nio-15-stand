#include "ch.hpp"
#include "hal.h"

#include "system.h"
#include "driver.h"
#include "app.h"

Battery battery;

int main(void) {
	halInit();
    System::init();

    chRegSetThreadName("main");

    Telemetry::instance();
    Terminal::instance();
    Connection::instance();

    FileSystem::init();
    Settings::init();
    //Log::instance();

    battery.init();
    encoderInit();
//    servoInit();
//    servoPower(TRUE);
    Adis::instance();
    Imu::instance();

//    controlInit();

    Thread::loop();
}
