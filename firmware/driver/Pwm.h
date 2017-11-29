/**	@authorTimur Muhanov
    @date 28.11.2017 */

#pragma once

#include <vector>
#include "hal.h"
#include "ch.hpp"

/*
 * timer2   ch1..4  = pwm1..4  pa0..3          af1
 * timer3   ch1..4  = pwm5..8  pc6..7  pb0..1  af2
 * timer4   ch4     = sound    pb9             af2
 */

class PwmChannel {
    public:
        PwmChannel(PWMDriver * driver, int channel) {
            _driver = driver;
            _channel = channel;
        }
        void setValue(float value) {
            pwmStart(_driver, _channel, value);
        }
    private:
        PWMDriver * _driver;
        int _channel;
};

class Actuator {
        Actuator() {
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
            _channels.emplace_back(PwmChannel(&PWMD2, 4));
        }

        void setLogicChannel(int channel, float value) {
            _channels[channel].setValue(value);
        }
    private:
        std::vector<PwmChannel> _channels;
};