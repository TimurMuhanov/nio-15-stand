#include "system/Connection.h"

// ****************** Connection ***************************
Connection::Connection(BaseAsynchronousChannel * channel) :
        _channel(channel),
        _heartbeatSender(channel, &_sdu_used),
        _parser(channel, &_sdu_used) {
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

    _parser._voltage = voltage;
    _parser._isReady = true;
}

// ****************** HeartbeatSender ***************************
Connection::HeartbeatSender::HeartbeatSender(BaseAsynchronousChannel * channel, bool* sdu_used) :
        _channel(channel),
        _sdu_used(sdu_used) {}

void Connection::HeartbeatSender::stop() {
    requestTerminate();
}

void Connection::HeartbeatSender::main() {
    setName("HeartbeatSender");

    mavlink_msg_heartbeat_pack(0,0,&rawMsg,0,0,0,0,0);
    int length = mavlink_msg_to_send_buffer(_buffer, &rawMsg);
    while(!shouldTerminate()) {
        while (*_sdu_used) {chThdSleepMilliseconds(10);};
        *_sdu_used = true;
        chnWriteTimeout(_channel, _buffer, length, TIME_IMMEDIATE);
        *_sdu_used = false;
        chThdSleepMilliseconds(1000);
    }

    exit(MSG_OK);
}

// ****************** Parser ***************************
Connection::Parser::Parser(BaseAsynchronousChannel * channel, bool* sdu_used) :
        _channel(channel),
        _sdu_used(sdu_used) {}

void Connection::Parser::stop() {
    requestTerminate();
}

void Connection::Parser::main() {
    setName("ConnectionParser");

    while(!shouldTerminate()) {
        if (_isReady) {
            _sysStatusMessage.voltage_battery = static_cast<uint16_t>((_voltage>0 ? _voltage : 0)*1000);
            mavlink_msg_sys_status_encode(0, 0, &_rawMavlinkMessage, &_sysStatusMessage);
            int length = mavlink_msg_to_send_buffer(_buffer, &_rawMavlinkMessage);
            _isReady = false;
            while (*_sdu_used) {chThdSleepMilliseconds(10);};
            *_sdu_used = true;
            chnWriteTimeout(_channel, _buffer, length, TIME_IMMEDIATE);
//        uint8_t b = ((uint8_t )(_voltage*10)&0xFF);// + (uint8_t)(*_sdu_used);
//        chnWrite(_channel,&b,1);
            *_sdu_used = false;
        }
        chThdSleepMilliseconds(100);

    }

    exit(MSG_OK);
}