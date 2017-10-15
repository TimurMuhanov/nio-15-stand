#include "driver/Led.h"


Led::Led(ioportid_t port, uint8_t pin, uint32_t periodMs) :
    _isRunning(false),
    _port(port),
    _pin(pin),
    _periodMs(periodMs) {

    palSetPad(_port, _pin);
}

Led::~Led() {
    if(_isRunning) {
        stop();
        wait();
    }
    palSetPad(_port, _pin);
}

void Led::setPeriod(uint32_t periodMs) {
    _mutex.lock();
    _periodMs = periodMs;
    _mutex.unlock();
}

bool Led::isRunning() const {
    return _isRunning;
}

void Led::start() {
    if(!_isRunning) {
        _isRunning = true;
        BaseStaticThread<1024>::start(LOWPRIO);
    }
}

void Led::stop() {
    if(_isRunning) {
        requestTerminate();
    }
}

void Led::main() {
    setName("Led");

    systime_t time = chVTGetSystemTime();
    while(!shouldTerminate()) {
        _mutex.lock();
        time += MS2ST(_periodMs);
        _mutex.unlock();
        palTogglePad(_port, _pin);
        sleepUntil(time);
    }

    _isRunning = false;
    exit(0);
}