#include "ch.h"
#include "hal.h"
#include "usbcfg.h"

#define Led_Blue        GPIOC_LED2
#define Led_Red         GPIOC_LED4
#define Led_Yellow      GPIOC_LED1

#define Led_Blue_b      0
#define Led_Red_b       1
#define Led_Yellow_b    2

// Class Led
/*
class Led {
public:
    Led(void *wsp, uint32_t tim_b, uint32_t tim_r, uint32_t tim_y) {
        time_ledb = tim_b;
        time_ledr = tim_r;
        time_ledy = tim_y;
        _lab_of_led = 7;
        chThdCreateStatic(wsp, sizeof(wsp), NORMALPRIO, ThreadLedBlue, NULL);
        chThdCreateStatic(wsp, sizeof(wsp), NORMALPRIO, ThreadLedRed, NULL);
        chThdCreateStatic(wsp, sizeof(wsp), NORMALPRIO, ThreadLedYellow, NULL);
    }
    void Set(uint8_t led_n, uint32_t led_time) {
        switch (led_n) {
            case Led_Blue:
                if (led_time != 0) {
                    time_ledb = led_time;
                } else {
                    _lab_of_led &= (0 << Led_Blue_b);
                }
                break;
            case Led_Red:
                if (led_time != 0) {
                    time_ledr = led_time;
                } else {
                    _lab_of_led &= (0 << Led_Red_b);
                }
                break;
            case Led_Yellow:
                if (led_time != 0) {
                    time_ledy = led_time;
                } else {
                    _lab_of_led &= (0 << Led_Yellow_b);
                }
                break;
            default :
                break;
        }
    }

private:
    uint8_t     _lab_of_led;
    uint32_t    time_ledb;
    uint32_t    time_ledy;
    uint32_t    time_ledr;
    void THD_FUNCTION(ThreadLedBlue,arg){
        (void)arg;
        chRegSetThreadName("blinker_blue");
        while (true) {
            //if (_lab_of_led&(1<<Led_Blue_b)) {
            palSetPad(GPIOC, Led_Blue);
            chThdSleepMilliseconds(time_ledb);
            palClearPad(GPIOC, Led_Blue);
            chThdSleepMilliseconds(time_ledb);
            // }
        }
    }
    void THD_FUNCTION(ThreadLedRed, arg) {
        (void)arg;
        chRegSetThreadName("blinker_red");
        while (true) {
            if (_lab_of_led&(1<<Led_Red_b)) {
                palSetPad(GPIOC, Led_Red);
                chThdSleepMilliseconds(time_ledr);
                palClearPad(GPIOC, Led_Red);
                chThdSleepMilliseconds(time_ledr);
            }
        }
    }
    void THD_FUNCTION(ThreadLedYellow, arg) {
        (void)arg;
        chRegSetThreadName("blinker_yellow");
        while (true) {
            if (_lab_of_led&(1<<Led_Yellow_b)) {
                palSetPad(GPIOC, Led_Yellow);
                chThdSleepMilliseconds(time_ledy);
                palClearPad(GPIOC, Led_Yellow);
                chThdSleepMilliseconds(time_ledy);
            }
        }
    }
};
*/

static THD_WORKING_AREA(waThread1, 128);
//static THD_FUNCTION(Thread1, arg) {
//
//    (void)arg;
//    chRegSetThreadName("blinker");
//    while (true) {
//        palSetPad(GPIOC, Led_Blue);
//        palSetPad(GPIOC, Led_Red);
//        palSetPad(GPIOC, Led_Yellow);
//        chThdSleepMilliseconds(1000);
//        palClearPad(GPIOC, Led_Blue);
//        palClearPad(GPIOC, Led_Red);
//        palClearPad(GPIOC, Led_Yellow);
//        chThdSleepMilliseconds(1000);
//    }
//}

static THD_WORKING_AREA(waThread2, 128);
static THD_WORKING_AREA(waThread3, 128);
static THD_WORKING_AREA(waThread4, 128);
uint8_t     _lab_of_led;
uint32_t    time_ledb;
uint32_t    time_ledr;
uint32_t    time_ledy;
static THD_FUNCTION(ThreadLedBlue,arg){
    (void)arg;
    chRegSetThreadName("blinker_blue");
    while (true) {
        if (_lab_of_led&(1<<Led_Blue_b)) {
        palSetPad(GPIOC, Led_Blue);
        chThdSleepMilliseconds(time_ledb);
        palClearPad(GPIOC, Led_Blue);
        chThdSleepMilliseconds(time_ledb);
        }
    }
}
static THD_FUNCTION(ThreadLedRed, arg) {
    (void)arg;
    chRegSetThreadName("blinker_red");
    while (true) {
        if (_lab_of_led&(1<<Led_Red_b)) {
            palSetPad(GPIOC, Led_Red);
            chThdSleepMilliseconds(time_ledr);
            palClearPad(GPIOC, Led_Red);
            chThdSleepMilliseconds(time_ledr);
        }
    }
}
static THD_FUNCTION(ThreadLedYellow, arg) {
    (void)arg;
    chRegSetThreadName("blinker_yellow");
    while (true) {
        if (_lab_of_led&(1<<Led_Yellow_b)) {
            palSetPad(GPIOC, Led_Yellow);
            chThdSleepMilliseconds(time_ledy);
            palClearPad(GPIOC, Led_Yellow);
            chThdSleepMilliseconds(time_ledy);
        }
    }
}

static THD_FUNCTION(ThreadSound, arg) {
    (void)arg;
    chRegSetThreadName("blinker_sound");
    while (true) {
        palSetPad(GPIOB, GPIOB_SOUND);
        chThdSleepMilliseconds(1);
        palClearPad(GPIOB, GPIOB_SOUND);
        chThdSleepMilliseconds(1);
    }
}

SerialUSBDriver SDU1;

int main(void) {

    halInit();
    chSysInit();

//    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    _lab_of_led = 0x7;
    time_ledb = 1000;
    time_ledr = 100;
    time_ledy = 50;
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, ThreadLedBlue, NULL);
    chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, ThreadLedRed, NULL);
    chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, ThreadLedYellow, NULL);
    chThdCreateStatic(waThread4, sizeof(waThread4), NORMALPRIO, ThreadSound, NULL);

    // com port over usb init
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);

    while (true) {
        chThdSleepMilliseconds(500);
        //unsigned char b = iqGet(&(&SDU1)->iqueue);
        sdPut(&SDU1,'A' );
        //oqPut(&(SDU1)->oqueue, b)
    }
}
