#include "ch.h"
#include "hal.h"
#include "usbcfg.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
        palSetPad(GPIOC, GPIOC_LED13);
        chThdSleepMilliseconds(1000);
        palClearPad(GPIOC, GPIOC_LED13);
        chThdSleepMilliseconds(1000);
    }
}

SerialUSBDriver SDU1;

int main(void) {

    halInit();
    chSysInit();

    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    // com port over usb init
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

//    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
//    usbConnectBus(serusbcfg.usbp);

    while (true) {
//        if (palReadPad(GPIOA, GPIOA_BUTTON))
        chThdSleepMilliseconds(500);
        //sdPut(&SDU1,sdGet(&SDU1));
//        unsigned char b = sdGet(&SDU1);
//        if (b == 0x42) {
//            sdPut(&SDU1,0x43);
//    }
        chSequentialStreamPut(&SDU1,'A');
    }
}
