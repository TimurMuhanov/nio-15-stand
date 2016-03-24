#include "log.h"
#include "io.h"
#include "imu.h"
#include "nav.h"
#include "encoder.h"
#include "servo.h"


FIL                 Log::_file;
thread_t* logUpdateThread;
static THD_FUNCTION(logUpdate, arg);
static THD_WORKING_AREA(logUpdateWorkingArea, 2048);

Log::Log() {
}

Log::~Log() {
}

void Log::init() {
    if( !FileSystem::isAvailable() )
        return;

    logUpdateThread = chThdCreateStatic( logUpdateWorkingArea,
                                        sizeof(logUpdateWorkingArea),
                                        NORMALPRIO, logUpdate, NULL);

    Thread::addThread( logUpdateThread, string("log") );
}

THD_FUNCTION(logUpdate, arg) {
    int i=0;
    string name;
    do {
        name = string("/log")+to_string(i++)+string(".log");
    } while( !FileSystem::open( Log::_file, name, FA_READ | FA_WRITE | FA_CREATE_NEW ) );

    /*  1x time
        3x accel
        3x gyro
        3x mag
        3x enc
        5x servo */
    string header = string("time\tax\tay\taz\tgx\tgy\tgz\tmx\tmy\tmz\trollE\tpitchE\tyawE\tleftAil\trightAil\tleftEle\trightEle\tRud\n");
    FileSystem::write( Log::_file, header );
    FileSystem::sync( Log::_file );

    systime_t time = chVTGetSystemTime();
    UINT len;
    char record[255];

    while( !chThdShouldTerminateX() ) {
        palTogglePad(GPIOC, 13);
        time += MS2ST(LOG_PERIOD_MS);

        vectorData accel = imuAccelGet();
        vectorData gyro = imuGyroGet();
        vectorData mag = imuMagGet();

        len = snprintf(record, 255, "% .3f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\n",
            accel.time,
            accel.x,
            accel.y,
            accel.z,
            gyro.x,
            gyro.y,
            gyro.z,
            mag.x,
            mag.y,
            mag.z,
            encoderGet(0).val,
            encoderGet(1).val,
            encoderGet(2).val,
            servoGet(0).val,
            servoGet(1).val,
            servoGet(2).val,
            servoGet(3).val,
            servoGet(4).val
        );
        FileSystem::write( Log::_file, (const u8*)record, len );
        FileSystem::sync( Log::_file );

        chThdSleepUntil(time);
    }
    chThdExit( 0 );
}
