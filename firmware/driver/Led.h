/** @author Timur Muhanov
    @data 15.10.2017 */

#pragma once

#include "hal.h"
#include "ch.hpp"

using namespace chibios_rt;

class Led : public BaseStaticThread<1024> {
    public:
        Led(ioportid_t port, uint8_t pin, uint32_t periodMs);
        ~Led();

        void setPeriod(uint32_t periodMs);

        bool isRunning() const;
        void start();
        void stop() override;

    private:
        void main() override;

        bool _isRunning;
        ioportid_t _port;
        uint8_t _pin;
        uint32_t _periodMs;
        Mutex _mutex;
};