/** @author Timur Muhanov
    @data 17.10.2017 */

#pragma once

#include "hal.h"
#include "ch.hpp"

using namespace chibios_rt;

class Battery : public BaseStaticThread<1024> {
public:
    Battery(uint32_t periodMs);
    ~Battery();

    float       _ADC;

    void start();
    void stop() override;

private:
    void main() override;
    uint32_t    _periodMs;
    Mutex       _mutex;
    uint8_t     _samples_num = 16;
    float       _mul = 0.00320388349514563106796116504854f;
};