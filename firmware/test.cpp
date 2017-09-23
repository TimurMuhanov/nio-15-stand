#include "ch.h"
#include "hal.h"

int main(void) {

    halInit();
    chSysInit();

    while (true) {
//        if (palReadPad(GPIOA, GPIOA_BUTTON))
            chThdSleepMilliseconds(500);
    }
}
