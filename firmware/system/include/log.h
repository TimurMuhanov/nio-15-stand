#ifndef LOG_H
#define LOG_H

#include "ch.hpp"
#include "ff.h"
#include <string>
#include "imu.h"


using namespace std;
using namespace chibios_rt;


#define LOG_PERIOD_MS   10
#define LOG_BUFFER_SIZE 512


class Log : public BaseStaticThread<2048> {
    private:
                                            Log();
                                           ~Log();
    public:

        static Log&                         instance() {
            static Log instance;
            return instance;
        }

        void                                write();

    private:
        FIL                                 _file;
        char                                _buffer[LOG_BUFFER_SIZE];
        vectorData                          _accel;
        vectorData                          _gyro;
        vectorData                          _mag;
        vectorData                          _rpy;
        scalarData                          _encoder0{0,0};
        scalarData                          _encoder1{0,0};
        scalarData                          _encoder2{0,0};
        scalarData                          _servo0{0,0};
        scalarData                          _servo1{0,0};
        scalarData                          _servo2{0,0};
        scalarData                          _servo3{0,0};
        scalarData                          _servo4{0,0};
        virtual void                        main(void);
};


#endif // LOG_H
