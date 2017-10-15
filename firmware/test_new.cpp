#include "ch.h"
#include "hal.h"
#include "driver/Led.h"
#include "usbcfg.h"

#define Led_Blue        GPIOC_LED2
#define Led_Red         GPIOC_LED4
#define Led_Yellow      GPIOC_LED1

#define Led_Blue_b      0
#define Led_Red_b       1
#define Led_Yellow_b    2

//static THD_FUNCTION(ThreadSound, arg) {
//    (void)arg;
//    chRegSetThreadName("blinker_sound");
//    while (true) {
//        palSetPad(GPIOB, GPIOB_SOUND);
//        chThdSleepMilliseconds(1);
//        palClearPad(GPIOB, GPIOB_SOUND);
//        chThdSleepMilliseconds(1);
//    }
//}

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
//
//    Led blueLed(GPIOC, Led_Blue, 400);
//    blueLed.start();

    while (true) {
        chThdSleepMilliseconds(500);
        chSequentialStreamPut(&SDU1,'A');
    }
}
