/**	@author Timur Muhanov
    @date 25.10.2017 */

#pragma once

#include <string>
#include "ch.hpp"
#include "hal.h"
#include "mavlink.h"

using namespace chibios_rt;

class Connection {
    public:
        Connection(BaseAsynchronousChannel * channel);
        ~Connection();

        void start();
        void stop();
        void wait();

        void sendBatteryStatus(float voltage);

    private:
        class HeartbeatSender : public BaseStaticThread<2048> {
            public:
                HeartbeatSender(BaseAsynchronousChannel * channel);

                void stop() override;

            private:
                void main() override;

                BaseAsynchronousChannel * _channel = nullptr;
        };

        class Parser : public BaseStaticThread<2048> {
            public:
                Parser(BaseAsynchronousChannel * channel);

                void stop() override;

            private:

                void main() override;

                BaseAsynchronousChannel * _channel = nullptr;
                mavlink_message_t _rawMavlinkMessage;
                mavlink_status_t _status;
        };

        BaseAsynchronousChannel * _channel = nullptr;

        uint8_t _buffer[MAVLINK_MAX_PACKET_LEN];
        mavlink_message_t _rawMavlinkMessage;
        mavlink_sys_status_t _sysStatusMessage;

        HeartbeatSender _heartbeatSender;
        Parser _parser;
};