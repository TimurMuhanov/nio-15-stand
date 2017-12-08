#include "driver/Pwm.h"

void PwmSetValue(int channel, float value)  {
    int ch;
    PWMDriver _PMWD;
    if (channel > 3) {
        ch = channel - 4;
        _PMWD = PWMD3;
    } else {
        ch = channel;
        _PMWD = PWMD2;
    }
    pwmEnableChannel(&_PMWD, ch, PWM_PERCENTAGE_TO_WIDTH(&_PMWD, value*100));
}

void Sound(int freq) {
    if (freq==0) {
        pwmDisableChannel(&PWMD4, 3);
    } else {
        PWMConfig _pwmConfig = {
                1000000,    //frequency
                (uint32_t)(1000000/freq),      //period
                NULL,
                {
                        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                },          //channels
                0,          //clock
                0           // *tim
        };
        pwmStart(&PWMD4, &_pwmConfig);
        pwmEnableChannel(&PWMD4, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD4, 5000));
    }

}