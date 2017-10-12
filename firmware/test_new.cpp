#include "ch.h"
#include "hal.h"
#include "usbcfg.h"

SerialUSBDriver SDU1;

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
//        palSetPad(GPIOC, GPIOC_LED13);
//        chThdSleepMilliseconds(1000);
//        palClearPad(GPIOC, GPIOC_LED13);
        sdPut(&SDU1,'A');
        chThdSleepMilliseconds(1000);
    }
}

int main(void) {

    halInit();
    chSysInit();

    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    // com port over usb init
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);

    while (true) {
        //chThdSleepMilliseconds(500);
        //unsigned char b = iqGet(&(&SDU1)->iqueue);
        sdPut(&SDU1,sdGet(&SDU1) +1 );
        //oqPut(&(SDU1)->oqueue, b)
    }
}
