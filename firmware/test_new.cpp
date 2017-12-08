#include "ch.h"
#include "hal.h"
#include "driver/Led.h"
#include "driver/Battery.h"
#include "system/Connection.h"
#include "usbcfg.h"
#include "mavlink.h"
#include "driver/Pwm.h"

SerialUSBDriver SDU1;

int main(void) {

    halInit();
    chSysInit();

    // com port over usb init
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);

    Led redLed(GPIOC, Led_Red, 1000);
    redLed.start();

    Led yellowLed(GPIOC, Led_Yellow, 4000);
    yellowLed.start();

    Led blueLed(GPIOC, Led_Blue, 400);
    blueLed.start();

    Connection conn((BaseAsynchronousChannel*)&SDU1);
    conn.start();

    Battery batt(100);
    batt.start();
    batt.setConnection(&conn);

    PwmSetValue(0,5);
    PwmSetValue(1,15);
    PwmSetValue(2,25);
    PwmSetValue(5,35);
    PwmSetValue(4,45);
    PwmSetValue(7,55);
    PwmSetValue(6,65);
    PwmSetValue(3,75);

    Sound(50);
    chThdSleepMilliseconds(1000);
    Sound(0);
    chThdSleepMilliseconds(1000);
    Sound(1000);
    chThdSleepMilliseconds(1000);
    Sound(0);

    while (true) {
        chThdSleepMilliseconds(1000);
    }

    batt.stop();
    conn.stop();

    batt.wait();
    conn.wait();
}
