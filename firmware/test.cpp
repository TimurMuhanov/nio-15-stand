#include "ch.h"
#include "hal.h"

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
        chThdSleepMilliseconds(100);
        palClearPad(GPIOC, GPIOC_LED13);
        chThdSleepMilliseconds(100);
    }
}

int main(void) {

    halInit();
    chSysInit();

    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    while (true) {
//        if (palReadPad(GPIOA, GPIOA_BUTTON))
            chThdSleepMilliseconds(500);
    }
}
