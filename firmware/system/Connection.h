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
                HeartbeatSender(BaseAsynchronousChannel * channel, bool* sdu_used);
                void stop() override;
            private:
                void main() override;
                uint8_t _buffer[MAVLINK_MAX_PACKET_LEN];
                mavlink_message_t rawMsg;
                BaseAsynchronousChannel * _channel = nullptr;
                bool *_sdu_used;
        };

        class Parser : public BaseStaticThread<2048> {
            public:
                Parser(BaseAsynchronousChannel * channel, bool* sdu_used);
                void stop() override;
                float _voltage = 0;
                bool _isReady = false;
            private:
                void main() override;
                BaseAsynchronousChannel * _channel = nullptr;
                mavlink_message_t _rawMavlinkMessage;
                mavlink_status_t _status;
                bool* _sdu_used;
                mavlink_sys_status_t _sysStatusMessage;
                uint8_t _buffer[MAVLINK_MAX_PACKET_LEN];
        };

        BaseAsynchronousChannel * _channel = nullptr;
        HeartbeatSender _heartbeatSender;
        Parser _parser;
        bool _sdu_used   =   false;
        bool  _isRunning = false;
};