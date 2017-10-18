/** @author Timur Muhanov
    @data 18.10.2017 */

#include "system/Serial.h"

Serial::Serial(BaseSequentialStream sdu, uint32_t periodMs, const mavlink_message_t *rawMsg, uint32_t bitrate) :
        _sdu(sdu),
        _bitrate(bitrate)   {
    _periodMs = periodMs;
    isRdyT = false;
    len_hb = mavlink_msg_to_send_buffer(buf_hb, rawMsg);
}

Serial::~Serial() {
    stop();
    wait();
}

void Serial::start() {
    BaseStaticThread<1024>::start(NORMALPRIO);
}

void Serial::stop() {
    requestTerminate();
}


uint8_t Serial::load(const mavlink_message_t *rawMsg) {
    if (!isRdyT) {
        _mutex.lock();
        len_msg = mavlink_msg_to_send_buffer(buf_msg, rawMsg);
        _mutex.unlock();
        isRdyT = true;
        return 0;
    }
    return 1;
}

void Serial::main() {
    setName("Serial");

    systime_t time = chVTGetSystemTime();
    while(!shouldTerminate()) {
        _mutex.lock();
        time += MS2ST(_periodMs);
        _mutex.unlock();
        // Отправляем сообщение синхронизации
        chSequentialStreamWrite(&_sdu, (uint8_t*)buf_hb, len_hb);
        // Если есть что слать
        if (isRdyT) {
            chSequentialStreamWrite(&_sdu, (uint8_t*)buf_msg, len_msg);
            isRdyT = false;
        }
        sleepUntil(time);
    }
    exit(0);
}

// Вариант решения проблемы отправки одного полезного сообщения в секунду
//void Serial::main() {
//    setName("Serial");
//
//    systime_t time_msg = chVTGetSystemTime();
//    systime_t time_hb = time_msg;
//
//    while(!shouldTerminate()) {
//
//        _mutex.lock();
//        time_hb += MS2ST(_periodMs);
//        time_msg += MS2ST((uint32_t)((len_msg*8/_bitrate)+1));
//        _mutex.unlock();
//
//        chSequentialStreamWrite(&_sdu, (uint8_t*)buf_hb, len_hb);
//
//        while ((time_msg)<(time_hb)) {
//            if (isRdyT) {
//                chSequentialStreamWrite(&_sdu, (uint8_t*)buf_msg, len_msg);
//                isRdyT = false;
//            }
//            sleepUntil(time_msg);
//            _mutex.lock();
//            time_msg += MS2ST((uint32_t)((len_msg*8/_bitrate)+1));
//            _mutex.unlock();
//        }
//
//        sleepUntil(time_hb);
//    }
//    exit(0);
//}