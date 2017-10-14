#include "ch.h"
#include "hal.h"
#include "usbcfg.h"
#include "chprintf.h"


static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
        palSetPad(GPIOC, GPIOC_LED1);
        palSetPad(GPIOC, GPIOC_LED2);
        palSetPad(GPIOC, GPIOC_LED3);
        palSetPad(GPIOC, GPIOC_LED4);
        chThdSleepMilliseconds(1000);
        palClearPad(GPIOC, GPIOC_LED1);
        palClearPad(GPIOC, GPIOC_LED2);
        palClearPad(GPIOC, GPIOC_LED3);
        palClearPad(GPIOC, GPIOC_LED4);
        chThdSleepMilliseconds(1000);
    }
}

SerialUSBDriver SDU1;

char fhex(uint8_t hex) {
    if(hex>9) {
        return 'A'+(hex-10);
    } else {
        return '0'+hex;
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

//    uint8_t buffer[512];
//    bool result = sdcRead(&SDCD1, 10, buffer, 512);
    BlockDeviceInfo inf;
    bool result = sdcGetInfo(&SDCD1, &inf);

    while (true) {
        chThdSleepMilliseconds(500);
        chprintf((BaseSequentialStream*)&SDU1, "%u %u %u\n\r", inf.blk_num, inf.blk_size, result);
    }
}
