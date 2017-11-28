#include "ch.h"
#include "hal.h"
#include "driver/Led.h"
#include "driver/Battery.h"
#include "system/Connection.h"
#include "usbcfg.h"
#include "mavlink.h"

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

    while (true) {
        chThdSleepMilliseconds(1000);
    }

    batt.stop();
    conn.stop();

    batt.wait();
    conn.wait();
}
