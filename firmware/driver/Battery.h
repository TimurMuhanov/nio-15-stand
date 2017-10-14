/**	@defgroup	Battery voltage reader
	@author		Zaripov Kamil
                                ADC converter
	@{ */

#ifndef BATTERY_H
#define BATTERY_H


#include "ch.hpp"
#include "hal.h"

using namespace chibios_rt;

class Battery : public BaseStaticThread<1024> {
    public:
                        Battery();
                       ~Battery();

        void            init();

    private:
        virtual void    main(void);
        float          _convert();
        u8             _samples_num = 16;
        u32            _update_time_us = 100000;
        float          _mul = 0.00320388349514563106796116504854;
};

#endif

/** @} */
