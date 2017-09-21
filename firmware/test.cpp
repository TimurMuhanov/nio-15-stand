/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "nil.h"
#include "hal.h"
//#include "test.h"
//F:/nio/nio15-new/firmware/cmake-build-debug/firmware
THD_WORKING_AREA(waThread1, 128);
THD_FUNCTION(Thread1, arg) {

    //palSetPadMode(GPIOC, GPIOC_LED, PAL_MODE_ALTERNATE(7));

    (void)arg;
    while (true) {
        palSetPad(GPIOC, GPIOC_LED);
        chThdSleepMilliseconds(500);
        palClearPad(GPIOC, GPIOC_LED);
        chThdSleepMilliseconds(500);
    }
}


THD_TABLE_BEGIN
                THD_TABLE_ENTRY(waThread1, "Thread1", Thread1, NULL)
THD_TABLE_END
int main(void) {

    halInit();
    chSysInit();

    palSetPad(GPIOC, GPIOC_LED);

    while (true) {
//        if (palReadPad(GPIOA, GPIOA_BUTTON))
            chThdSleepMilliseconds(500);
    }
}