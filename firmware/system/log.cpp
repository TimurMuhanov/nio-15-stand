#include "log.h"
#include "io.h"
#include "imu.h"
#include "nav.h"
#include "encoder.h"
#include "servo.h"


FIL                 Log::_file;
thread_t* logUpdateThread;
extern "C" THD_FUNCTION(logUpdate, arg);
static THD_WORKING_AREA(logUpdateWorkingArea, 512);

Log::Log() {
}

Log::~Log() {
}

void Log::init() {
    // open file
    if( sdCardInited() ) {
        //FRESULT res;

        int i=0;
        string name;
        do {
            name = string("/log")+to_string(i++)+string(".log");
        } while( f_open(&_file, name.c_str(), FA_READ | FA_WRITE | FA_CREATE_NEW ) != FR_OK );

        string header;
        UINT res;
        /*
        1x time
        3x accel
        3x gyro
        3x mag
        3x enc
        5x servo
        */
        header = string("time\tax\tay\taz\tgx\tgy\tgz\tmx\tmy\tmz\trollE\tpitchE\tyawE\tleftAil\trightAil\tleftEle\trightEle\tRud");
        f_write( &_file, header.c_str(), header.length(), &res );
    }

    f_sync( &_file );
    logUpdateThread = chThdCreateStatic( logUpdateWorkingArea,
                                        sizeof(logUpdateWorkingArea),
                                        NORMALPRIO, logUpdate, NULL);

    Thread::addThread( logUpdateThread, string("log") );
}

THD_FUNCTION(logUpdate, arg) {
    systime_t time = chVTGetSystemTime();
    UINT len;
    UINT res;
    char record[255];

    while( !chThdShouldTerminateX() ) {
        time += MS2ST(LOG_PERIOD_MS);

        vectorData accel = imuAccelGet();
        vectorData gyro = imuGyroGet();
        vectorData mag = imuMagGet();

        len = sprintf(record, "%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n",
            accel.time,
            accel.x,
            accel.y,
            accel.z,
            gyro.x,
            gyro.x,
            gyro.x,
            mag.x,
            mag.x,
            mag.x,
            encoderGet(0).val,
            encoderGet(1).val,
            encoderGet(2).val,
            servoGet(0).val,
            servoGet(1).val,
            servoGet(2).val,
            servoGet(3).val,
            servoGet(4).val
        );
        f_write( &Log::_file, record, len, &res );

        f_sync( &Log::_file );

        chThdSleepUntil(time);
    }
    chThdExit( 0 );
}
