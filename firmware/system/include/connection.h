/**	@defgroup	CONNECTION
	@author		Zaripov Kamil
				Communicate with Ground Control Station
	@{ */

#ifndef CONNECTION_H
#define CONNECTION_H


#define MAVLINK_DEFAULT_COMM		MAVLINK_COMM_0


#include "ch.hpp"
#include "hal.h"
#include "Thread.h"
#include "Telemetry.h"
#include "Imu.h"
#include "mavlink_bridge_header.h"
#include "mavlink.h"


using namespace chibios_rt;


class Connection : public BaseStaticThread<2048> {
                                            Connection();
                                           ~Connection();
    public:
        static Connection&                  instance() {
            static Connection instance;
            return instance;
        }

        void                                valueSend(u32 time, string key, float value);
        void                                vectorValueSend(u32 time, string key, Vector<3> v);
        void                                quatValueSend(u32 time, string key, Quaternion<> q);

        /**	set cpu udage
        @param      usage       cpu usage in range 0..1 */
        void                                setCpuInfo( float cpuUsage, u32 time, u32 threadCount );

        Mutex                               _mutex;
    private:
        virtual void                        main(void);
};


#endif

/** @} */
