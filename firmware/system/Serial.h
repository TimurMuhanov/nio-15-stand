/** @author Timur Muhanov
    @data 18.10.2017 */

#ifndef FIRMWARE_SERIAL_H
#define FIRMWARE_SERIAL_H

#include "hal.h"
#include "ch.hpp"
#include "mavlink.h"

#define Size_Buf_Serial 256U;

using namespace chibios_rt;

class Serial : public BaseStaticThread<1024> {
public:
    Serial(BaseSequentialStream sdu, uint32_t periodMs, const mavlink_message_t *rawMsg, uint32_t bitrate);
    ~Serial();

    void start();
    void stop() override;
    uint8_t load(const mavlink_message_t *rawMsg);

private:
    void main() override;

    BaseSequentialStream _sdu;
    bool isRdyT;
    uint32_t _periodMs;
    int len_hb;
    int len_msg;
    uint8_t buf_hb[MAVLINK_MAX_PACKET_LEN];
    uint8_t buf_msg[MAVLINK_MAX_PACKET_LEN];
    Mutex _mutex;
    uint32_t _bitrate;
};

#endif //FIRMWARE_SERIAL_H