#include "Battery.h"
#include "Connection.h"

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


Battery::Battery() {

}

Battery::~Battery() {

}

void Battery::init() {
    start(HIGHPRIO);
}

void Battery::main() {
    setName( "Imu" );

    systime_t time = chVTGetSystemTime();
    while( !shouldTerminate() ) {
//        static systime_t oldTime = chVTGetSystemTime();
//        float dt = ST2US(chVTGetSystemTime() - oldTime)/1.0e6f;
//        oldTime = chVTGetSystemTime();

        time += US2ST(_update_time_us);

        Connection::instance().valueSend( chVTGetSystemTime()/10, "bat", _convert() );

        chThdSleepUntil(time);
    }

    exit(0);
}

float Battery::_convert() {
    uint16_t buffer[_samples_num];
    float avg;

    adcConvert(&BOARD_BATTERY_ADC_DEVICE, &adc_conv_group, buffer, _samples_num);

    for (size_t i = 0; i < _samples_num; i++) {
        avg += buffer[i];
    }

    avg *= _mul/_samples_num;

    return avg;
}
