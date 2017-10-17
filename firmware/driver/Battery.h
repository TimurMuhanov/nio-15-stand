/** @author Timur Muhanov
    @data 17.10.2017 */

#pragma once

#include "hal.h"
#include "ch.hpp"

#define firstInitADC 0x8000;
#define BOARD_BATTERY_ADC_DEVICE ADCD1

using namespace chibios_rt;

class Batt : public BaseStaticThread<1024> {
public:
    Batt(uint32_t periodMs);
    ~Batt();

    float       _ADC;

    void start();
    void stop() override;

private:
    void main() override;
    uint32_t    _periodMs;
    Mutex       _mutex;
    uint8_t     _samples_num = 16;
    float       _mul = 0.00320388349514563106796116504854;
};