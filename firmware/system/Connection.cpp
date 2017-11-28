#include "system/Connection.h"

// ****************** Connection ***************************
Connection::Connection(BaseAsynchronousChannel * channel) :
        _channel(channel),
        _heartbeatSender(channel),
        _parser(channel) {
}

Connection::~Connection() {
    stop();
    wait();
}

void Connection::start() {
    if (!_isRunning) {
        _isRunning = true;
        _heartbeatSender.start(LOWPRIO);
        _parser.start(HIGHPRIO);
    }
}

void Connection::stop() {
    if (_isRunning) {
        _isRunning = false;
        _heartbeatSender.stop();
        _parser.stop();
    }
}

void Connection::wait() {
    _heartbeatSender.wait();
    _parser.wait();
}

void Connection::sendBatteryStatus(float voltage) {
    if(_channel == nullptr) {
        return;
    }

    _sysStatusMessage.voltage_battery = static_cast<uint16_t>((voltage>0 ? voltage : 0)*1000);
    mavlink_msg_sys_status_encode(0, 0, &_rawMavlinkMessage, &_sysStatusMessage);
    int length = mavlink_msg_to_send_buffer(_buffer, &_rawMavlinkMessage);
    chnWriteTimeout(_channel, _buffer, length, TIME_IMMEDIATE);
}

// ****************** HeartbeatSender ***************************
Connection::HeartbeatSender::HeartbeatSender(BaseAsynchronousChannel * channel) : _channel(channel) {}

void Connection::HeartbeatSender::stop() {
    requestTerminate();
}

void Connection::HeartbeatSender::main() {
    setName("HeartbeatSender");

    mavlink_msg_heartbeat_pack(0,0,&rawMsg,0,0,0,0,0);
    int length = mavlink_msg_to_send_buffer(_buffer, &rawMsg);
    while(!shouldTerminate()) {
        chnWriteTimeout(_channel, _buffer, length, TIME_IMMEDIATE);
        chThdSleepMilliseconds(1000);
    }

    exit(MSG_OK);
}

// ****************** Parser ***************************
Connection::Parser::Parser(BaseAsynchronousChannel * channel) : _channel(channel) {}

void Connection::Parser::stop() {
    requestTerminate();
}

void Connection::Parser::main() {
    setName("ConnectionParser");

    while(!shouldTerminate()) {
        msg_t byte = chnGetTimeout(_channel, MS2ST(500));   // Что происходит?
        if(byte == MSG_TIMEOUT) {
            continue;
        }

        if (mavlink_parse_char(0, (uint8_t)byte, &_rawMavlinkMessage, &_status)) {
            ;
        }
    }

    exit(MSG_OK);
}