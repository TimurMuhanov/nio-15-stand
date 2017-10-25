#include "system/Connection.h"


Connection::Connection(BaseAsynchronousChannel * channel) :
        _heartbeatSender(channel),
        _parser(channel) {
}

Connection::~Connection() {
    stop();
    wait();
}

void Connection::start() {
    _heartbeatSender.start(LOWPRIO);
    _parser.start(HIGHPRIO);
}

void Connection::stop() {
    _heartbeatSender.stop();
    _parser.stop();
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

Connection::HeartbeatSender::HeartbeatSender(BaseAsynchronousChannel * channel) : _channel(channel) {}

void Connection::HeartbeatSender::stop() {
    requestTerminate();
}

void Connection::HeartbeatSender::main() {
    setName("HeartbeatSender");

    while(!shouldTerminate()) {

    }

    exit(MSG_OK);
}

Connection::Parser::Parser(BaseAsynchronousChannel * channel) : _channel(channel) {}

void Connection::Parser::stop() {
    requestTerminate();
}

void Connection::Parser::main() {
    setName("ConnectionParser");

    while(!shouldTerminate()) {
        msg_t byte = chnGetTimeout(_channel, MS2ST(500));
        if(byte == MSG_TIMEOUT) {
            continue;
        }

        if (mavlink_parse_char(0, (uint8_t)byte, &_rawMavlinkMessage, &_status)) {
            ;
        }
    }

    exit(MSG_OK);
}