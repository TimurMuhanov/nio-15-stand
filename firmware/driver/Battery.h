/** @author Timur Muhanov
    @data 17.10.2017 */

#pragma once

#include "hal.h"
#include "ch.hpp"
#include "system/Connection.h"

using namespace chibios_rt;

class Battery : public BaseStaticThread<1024> {
    public:
        Battery(uint32_t periodMs);
        ~Battery();

        void start();
        void stop() override;

        void setConnection(Connection * connection);

    private:
        void main() override;
        uint32_t    _periodMs;
        uint8_t     _samples_num = 16;
        float       _mul = 0.00320388349514563106796116504854f;
        Connection * _connection = nullptr;
};