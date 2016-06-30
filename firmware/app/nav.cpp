#include "nav.h"
#include "Terminal.h"
#include <math.h>
#include <thread.h>

static thread_t* updateThread;
static THD_FUNCTION(update, arg);
static THD_WORKING_AREA(updateWorkingArea, 8192);

#define gyroMeasError ((24.0f / 180.0f) * M_PI) // gyroscope measurement error in rad/s (shown as 6 deg/s)
#define gyroMeasDrift ((0.1f / 180.0f) * M_PI) // gyroscope measurement error in rad/s/s (shown as 0.3f deg/s/s)

#define beta (sqrt(3.0f / 4.0f) * gyroMeasError) // compute beta
#define zeta (sqrt(3.0f / 4.0f) * gyroMeasDrift) // compute zeta

static binary_semaphore_t dataAccess;
vectorData rpy;

Quaternion<> q;

void navInit(void){
    chBSemObjectInit(&dataAccess, false);

    updateThread = chThdCreateStatic(   updateWorkingArea,
                                        sizeof(updateWorkingArea),
                                        NORMALPRIO, update, NULL);
    Thread::addThread( updateThread, string("nav") );
}

Matrix<4,3> Jt_E(Quaternion<> q, Vector<3> d){
    Matrix<4,3> Jt;
    Jt(0,0) =                2.0f * (d.y() * q.z() - d.z() * q.y());               Jt(0,1) =                2.0f * (d.z() * q.x() - d.x() * q.z());              Jt(0,2) =                2.0f * (d.x() * q.y() - d.y() * q.x());
    Jt(1,0) =                2.0f * (d.y() * q.y() + d.z() * q.z());               Jt(1,1) = 2.0f * d.x() * q.y() - 4.0f * d.y() * q.x() + 2.0f * d.z() * q.w(); Jt(1,2) =  2.0f * d.x() * q.z() - 4.0f * d.z() * q.x() - 2.0f * d.y() * q.w();
    Jt(2,0) =  2.0f * d.y() * q.x() - 4.0f * d.x() * q.y() - 2.0f * d.z() * q.w(); Jt(2,1) =                2.0f * (d.x() * q.x() + d.z() * q.z());              Jt(2,2) =  2.0f * d.x() * q.w() - 4.0f * d.z() * q.y() + 2.0f * d.y() * q.z();
    Jt(3,0) =  2.0f * d.y() * q.w() - 4.0f * d.x() * q.z() + 2.0f * d.z() * q.x(); Jt(3,1) = 2.0f * d.z() * q.y() - 4.0f * d.y() * q.z() - 2.0f * d.x() * q.w(); Jt(3,2) =                2.0f * (d.x() * q.x() + d.y() * q.y());
    return Jt;
}

Quaternion<> q_Earth_to_Frame(Vector<3> i_Earth_in_Frame, Vector<3> j_Earth_in_Frame){
    Vector<3> r1 = i_Earth_in_Frame - Vector<3>{1.0, 0.0, 0.0};
    Vector<3> r2 = j_Earth_in_Frame - Vector<3>{0.0, 1.0, 0.0};
    Vector<3> s2 = j_Earth_in_Frame + Vector<3>{0.0, 1.0, 0.0};
    Quaternion<> returnQuaternion;
    returnQuaternion.scalar() = r1 * s2;
    returnQuaternion.vector() = r2 ^ r1;
    return returnQuaternion.normalized();
}

// Function to compute one filter iteration
void filterUpdate(Vector<3> gyro, Vector<3> accel, Vector<3> mag) {
    // local system variables
    const Vector<3> Ae{0, 1, 0};
    static Vector<3> Me{1, 0, 0}, gyroB{0.0, 0.0, 0.0};
    Quaternion<> qPre, qFromGyro, qFromAccelMag;
    Vector<3> gyroError;

    static systime_t oldTime = chVTGetSystemTime();
    float dt = ST2US(chVTGetSystemTime() - oldTime)/1.0e6f;
    oldTime = chVTGetSystemTime();

    qPre = (q * Quaternion<>(0,gyro))*0.5f;

    // compute flux in the earth frame
    mag = (qPre * mag * qPre.conjugated()).vector();
    mag(1) = 0;
    mag = (qPre.conjugated() * mag * qPre).vector();
    mag.normalized();

    // compute the quaternion from gravity field oreentation
    std::function< Vector<6>( Vector<4>) > f = ([&] (Vector<4> q) -> Vector<6> {
        Vector<3> fromAccel = (Quaternion<>(q).conjugated() * Ae * Quaternion<>(q)).vector() - accel;
        Vector<3> fromMag = (Quaternion<>(q).conjugated() * Me * Quaternion<>(q)).vector() - mag;
        return Vector<6>{ fromAccel(0), fromAccel(1), fromAccel(2), fromMag(0), fromMag(1), fromMag(2) };
    });
    qFromAccelMag = jacobian(f, (Vector<4>)q).transponced() * f(q);
    qFromAccelMag.normalize();

    // compute angular estimated direction of the gyroscope error
    gyroError = (q.conjugated() * qFromAccelMag).vector()*2.0f;
    //print("gyro %f %f %f \n\r", gyro(0),gyro(1),gyro(2));
    // compute and remove the gyroscope baises
    gyroB = gyroB + gyroError * dt * zeta;
    //print("B %f %f %f \n\r", gyroB(0),gyroB(1),gyroB(2));
    gyro = gyro - gyroB;
    //print("res %f %f %f \n\r", gyro(0),gyro(1),gyro(2));

    // compute the quaternion rate measured by gyroscopes
    qFromGyro = (q * Quaternion<>(0,gyro))*0.5f;

    // compute then integrate the estimated quaternion rate
    q = q + (qFromGyro - (beta * qFromAccelMag)) * dt;
    // normalise quaternion
    q.normalize();
}

THD_FUNCTION(update, arg) {
//    systime_t chibios_time = chVTGetSystemTime();
    Vector<3> gyro, accel, mag;
    Vector<3> gyroDrift{0, 0, 0};
    Vector<3> i,j;
    int count = 0;

    while( !chThdShouldTerminateX() ) {
//        chibios_time += MS2ST(NAV_UPDATE_PERIOD_MS);

//        gyro = {imuGyroGet().x, imuGyroGet().y, imuGyroGet().z};
//        gyro = (M_PI/180.0f) * gyro;
//        accel = {imuAccelGet().x, imuAccelGet().y, imuAccelGet().z};
//        mag = {imuMagGet().x, imuMagGet().y, imuMagGet().z};

        accel.normalize();
        mag.normalize();

        if( count < CALIBRATE_STEPS ) {
            gyroDrift = gyroDrift + gyro;
            ++count;
        } else if( count == CALIBRATE_STEPS ) {
            gyroDrift = gyroDrift/CALIBRATE_STEPS;
            j = accel;
            i = (mag - j * (mag * j)).normalized();
            q = q_Earth_to_Frame(i, j);
            ++count;


        } else {
            chBSemWait(&dataAccess);
            filterUpdate(gyro-gyroDrift, accel, mag);
            chBSemSignal(&dataAccess);
            //print("q %f %f %f %f \n\r", q.w(), q.x(), q.y(), q.z());
            //print("accel %f %f %f \n\r", accel(0), accel(1), accel(2));
            //print("mag %f %f %f \n\r", mag(0), mag(1), mag(2));
            //print("i %f %f %f \n\r", i(0), i(1), i(2));
            //print("j %f %f %f \n\r\n\r", j(0), j(1), j(2));
        }

        //углы Эйлера в радианах
        chBSemWait(&dataAccess);
        rpy.time = chVTGetSystemTime();
//        rpy.x = atan2(2*(q.w()*q.x() + q.y()*q.z()), 1 - 2*(q.x()*q.x() + q.y()*q.y()));
//        rpy.y = atan2(2*(q.w()*q.z() + q.x()*q.y()), 1 - 2*(q.y()*q.y() + q.z()*q.z()));
//        rpy.z = asin(2*(q.w()*q.y() - q.z()*q.x()));
        chBSemSignal(&dataAccess);

//        chThdSleepUntil(chibios_time);
        chThdSleepMilliseconds(NAV_UPDATE_PERIOD_MS);
    }
}

quaternionData get_quat(void) {
    quaternionData ret = {0,0,0,0,0};
    chBSemWait(&dataAccess);
    ret.time = rpy.time;
    ret.w = q.w();
    ret.x = q.x();
    ret.y = q.y();
    ret.z = q.z();
    chBSemSignal(&dataAccess);
    return ret;
}

vectorData get_rpy(void) {
    vectorData ret;
//    vectorData ret = {0,0,0,0};
//    chBSemWait(&dataAccess);
//    ret.time = rpy.time;
//    ret.x = rpy.x;
//    ret.y = rpy.y;
//    ret.z = rpy.z;
//    chBSemSignal(&dataAccess);
    return ret;
}



//    // compute the quaternion from gravity field oreentation
//    std::function< Vector<3>( Vector<4>) > fAccel = ([&] (Vector<4> q) -> Vector<3> {
//         return (Quaternion<>(q).conjugated() * Ae * Quaternion<>(q)).vector() - accel;
//    });
//    qFromAccel = jacobian(fAccel, (Vector<4>)q).transponced() * fAccel(q);

//    // compute the quaternion from gravity field oreentation
//    std::function< Vector<3>( Vector<4>) > fMag = ([&] (Vector<4> q) -> Vector<3> {
//         return (Quaternion<>(q).conjugated() * Me * Quaternion<>(q)).vector() - accel;
//    });
//    qFromMag = jacobian(fMag, (Vector<4>)q).transponced() * fMag(q);

//    qFromAccelMag = qFromAccel + qFromMag;

