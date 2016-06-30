/**	@defgroup	ADIS16488
	@author		Zaripov Kamil
				Driver for ADIS16488 sensor
	@{ */

#ifndef ADIS16488_H
#define ADIS16488_H


#include "ch.hpp"
#include "PubSub.h"
#include "g_matrix.h"
#include "g_vector.h"
#include "g_quaternion.h"

#define	ADIS_BUFFER_SIZE	20
#define	ADIS_UPDATE_PERIOD	2

using namespace geometry;
using namespace chibios_rt;


class Adis : public BaseStaticThread<4096> {
                                            Adis();
                                           ~Adis();
    public:
        static Adis&                        instance();

        static Topic<vectorData>            accel;
        static Topic<vectorData>            gyro;
        static Topic<vectorData>            mag;
        static Topic<scalarData>            temp;
        static Topic<scalarData>            press;
    private:
        virtual void                        main(void);
        void                                init();
        bool                                testConnection();
        void                                read( u8 page, u8 address, u32 length, u16* buffer );
        void                                write( u8 page, u8 address, u32 length, const u16* buffer );

        u16                                 txBuffer[ADIS_BUFFER_SIZE];
        u16                                 rxBuffer[ADIS_BUFFER_SIZE];
};

#endif

/** @} */
