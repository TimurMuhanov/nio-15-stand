#include "Log.h"
#include "FileSystem.h"
#include "encoder.h"
#include "servo.h"

#define RAD_DEG(rad) (rad/M_PI*180)
#define DEG_RAD(deg) (deg/180*M_PI)


Log::Log() {
    if( !FileSystem::isAvailable() )
        return;

    int i=0;
    string name;
    do {
        name = string("/log")+to_string(i++)+string(".log");
    } while( !FileSystem::open( _file, name, FA_READ | FA_WRITE | FA_CREATE_NEW ) );

    string header = string("time\trollImu\tpitchImu\tyawImu\trollE\tpitchE\tyawE\n");
    FileSystem::write( _file, header );
    FileSystem::sync( _file );

//    start(NORMALPRIO);
}

Log::~Log() {}

void Log::write() {
    palSetPad(GPIOC, 13);

//    _rpy = Imu::getRpy();
    encoderFix();
    _encoder0 = encoderGet(0);
    _encoder1 = encoderGet(1);
    _encoder2 = encoderGet(2);

    UINT len = snprintf(_buffer, LOG_BUFFER_SIZE, "%.3f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\n",
      (_rpy.time)/10000.0f,
       RAD_DEG(_rpy.val(0)), RAD_DEG(_rpy.val(1)), RAD_DEG(_rpy.val(2)),
       _encoder0.val, _encoder1.val, _encoder2.val
    );
    FileSystem::write( _file, (const u8*)_buffer, len );
    FileSystem::sync( _file );

    palClearPad(GPIOC, 13);
}

char logName[] = "logger";

void Log::main() {
    setName( "logger" );
    int i=0;
    string name;
    do {
        name = string("/log")+to_string(i++)+string(".log");
    } while( !FileSystem::open( _file, name, FA_READ | FA_WRITE | FA_CREATE_NEW ) );

    /*  1x time
        3x accel
        3x gyro
        3x mag
        3x enc
        5x servo */
//    string header = string("time\tax\tay\taz\tgx\tgy\tgz\tmx\tmy\tmz\trollE\tpitchE\tyawE\tleftAil\trightAil\tleftEle\trightEle\tRud\n");
    /*  1x time
        3x accel
        3x gyro
        3x mag
        4x quaterion
        3x enc */
    string header = string("time\tax\tay\taz\tgx\tgy\tgz\tmx\tmy\tmz\tq0\tq1\tq2\tq3\trollE\tpitchE\tyawE\n\r");
    FileSystem::write( _file, header );
    FileSystem::sync( _file );

//    UINT len = 0;

    systime_t time = chVTGetSystemTime();
    while( !shouldTerminate() ) {
        time += MS2ST(LOG_PERIOD_MS);
        palSetPad(GPIOC, 13);

//        _accel = Imu::accel.get();
//        _gyro = Imu::gyro.get();
//        _mag = Imu::mag.get();
//        _q = Imu::getQuat();
//        _encoder0 = encoderGet(0);
//        _encoder1 = encoderGet(1);
//        _encoder2 = encoderGet(2);
//        servo0 = servoGet(0);
//        servo1 = servoGet(1);
//        servo2 = servoGet(2);
//        servo3 = servoGet(3);
//        servo4 = servoGet(4);

//        len = snprintf(_buffer, LOG_BUFFER_SIZE, "% .3f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\t% .6f\n\r",
//           _q.time,
//           _accel.val(0), _accel.val(1), _accel.val(2),
//           _gyro.val(0), _gyro.val(1), _gyro.val(2),
//           _mag.val(0), _mag.val(1), _mag.val(2),
//           _q.val(0), _q.val(1), _q.val(2), _q.val(3),
//           _encoder0.val, _encoder1.val, _encoder2.val
//        );
//        FileSystem::write( _file, (const u8*)_buffer, len );
//        FileSystem::sync( _file );

        palClearPad(GPIOC, 13);

        chThdSleepUntil(time);
    }
    exit( 0 );
}
