#include "ch.h"
#include "hal.h"
#include "usbcfg.h"
#include "chprintf.h"
#include "ff.h"


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

FATFS filesystem;

int main(void) {

    halInit();
    chSysInit();

    Led led;
    led.blink(Led::Blue, 1000);

    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    // com port over usb init
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);

    bool connectResult = sdcConnect(&SDCD1);

    uint8_t buffer[512];
    bool readResult = sdcRead(&SDCD1, 0, buffer, 512);

    sdcflags_t err = sdcGetAndClearErrors(&SDCD1);

//    bool mountResult = f_mount(&filesystem, "", 1 );
//
//    DIR dir;
//    FRESULT openResult = f_opendir (&dir, ".");

//    TCHAR label[256];
//    DWORD unused;
//    FRESULT labelResult = f_getlabel("", label, &unused);


    while (true) {
        chThdSleepMilliseconds(500);
        chprintf((BaseSequentialStream*)&SDU1, "\n\r%u %u %X\n\r", connectResult, readResult, err);
//        for(int i=0;i<512;++i) {
//            chprintf((BaseSequentialStream*)&SDU1, "%x ", buffer[i]);
//        }
    }
}
