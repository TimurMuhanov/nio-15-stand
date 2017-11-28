#include "driver/Battery.h"

static ADCConversionGroup adc_conv_group = {
        FALSE,                              // circular buffer
        (uint16_t)(1),                      // number of channels
        NULL,                               // callback function
        NULL,
        0,                                  // CR1 register
        ADC_CR2_SWSTART,                    // CR2 register
        ADC_SMPR1_SMP_AN13(ADC_SAMPLE_56),  // SMPR1 register
        0,                                  // SMPR2 register
        ADC_SQR1_NUM_CH(1),                 // SQR1 register. Set channel sequence length
        0,                                  // SQR2 register
        ADC_SQR3_SQ1_N(ADC_CHANNEL_IN13)	// SQR3 register, select 1 channels: 13
};

Battery::Battery(uint32_t periodMs) :
        _periodMs(periodMs) {
}

Battery::~Battery() {
    stop();
    wait();
}

void Battery::start() {    // can to use without overloading
    BaseStaticThread<1024>::start(NORMALPRIO);
}

void Battery::stop() {
    requestTerminate();
}

void Battery::setConnection(Connection * connection) {
    _connection = connection;
}

void Battery::main() {
    setName("Battery");

    uint16_t    buffer[_samples_num];
    float       avg;
    systime_t   time = chVTGetSystemTime();

    while(!shouldTerminate()) {
        time += MS2ST(_periodMs);
        // Делаются замеры АЦП
        avg = 0;
        adcConvert(&BOARD_BATTERY_ADC_DEVICE, &adc_conv_group, buffer, _samples_num);
        for (size_t i = 0; i < _samples_num; i++) {
            avg += buffer[i];
        }
        avg *= _mul/_samples_num;

        if(_connection != nullptr) {
            _connection->sendBatteryStatus(avg);
        }

        sleepUntil(time);
    }

    exit(MSG_OK);
}