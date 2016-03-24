#include "nav.h"
#include "io.h"
#include <math.h>
#include <thread.h>

static thread_t* updateThread;
static THD_FUNCTION(update, arg);
static THD_WORKING_AREA(updateWorkingArea, 4096);

#define gyroMeasError (6.0f / 180.0f) * M_PI // gyroscope measurement error in rad/s (shown as 6 deg/s)
//#define gyroMeasDrift (0.3f / 180.0f) * M_PI// gyroscope measurement error in rad/s/s (shown as 0.3f deg/s/s)
#define deltat (NAV_UPDATE_PERIOD_MS / 1000.0f)

static binary_semaphore_t dataAccess;
vectorData rpy;
Vector<3> zeta;

//Vector<3> mag_id{16.502, -49.709, 3.162}; //magnetic field coeff
Quaternion<> q{1,0,0,0};

void navInit(void){
    chBSemObjectInit(&dataAccess, false);

    updateThread = chThdCreateStatic(   updateWorkingArea,
                                        sizeof(updateWorkingArea),
                                        NORMALPRIO, update, NULL);
    Thread::addThread( updateThread, string("nav") );
}

/*scalarData Vect_abs(vectorData data){
    scalarData absol;
    absol.val = sqrt((data.x)*(data.x) + (data.y)*(data.y) + (data.z)*(data.z));
    absol.time = data.time;
    return absol;
}

scalarData Quat_abs(quaternionData data){
    scalarData absol;
    absol.val = sqrt((data.w) * (data.w) + (data.x)*(data.x) + (data.y)*(data.y) + (data.z)*(data.z));
    absol.time = data.time;
    return absol;
}

vectorData Vect_norm(vectorData data){
    vectorData norm;
        if(Vect_abs(data).val==0) return data;
        norm.x = data.x / Vect_abs(data).val;
        norm.y = data.y / Vect_abs(data).val;
        norm.z = data.z / Vect_abs(data).val;
        norm.time = Vect_abs(data).time;
    return norm;
}

quaternionData Quat_norm(quaternionData data){
    quaternionData norm;
    if(Quat_abs(data).val==0) return data;
    norm.w = data.w / Quat_abs(data).val;
    norm.x = data.x / Quat_abs(data).val;
    norm.y = data.y / Quat_abs(data).val;
    norm.z = data.z / Quat_abs(data).val;
    norm.time = Quat_abs(data).time;
    return norm;
}

quaternionData q_mult_q(quaternionData a, quaternionData b){
    quaternionData res;
    res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    return res;
}

quaternionData q_invert(quaternionData q){
    quaternionData res;
    res.w = q.w;
    res.x = -q.x;
    res.y = -q.y;
    res.z = -q.z;
    return res;
}

vectorData v_transform(quaternionData q, vectorData v){
    vectorData res;
    quaternionData temp;
    temp = q_mult_v(q,v);
    temp = q_mult_q(temp,q_invert(q));
    res.x = temp.x;
    res.y = temp.y;
    res.z = temp.z;
    res.time = q.time;
    return res;
}

quaternionData q_mult_v(quaternionData a, vectorData b){
        quaternionData res;
        res.w = -a.x * b.x - a.y * b.y - a.z * b.z;
        res.x = a.w * b.x + a.y * b.z - a.z * b.y;
        res.y = a.w * b.y - a.x * b.z + a.z * b.x;
        res.z = a.w * b.z + a.x * b.y - a.y * b.x;
        return res;
}
*/

Matrix<4,3> Jt_E(Quaternion<> q, Vector<3> d){
    Matrix<4,3> Jt;
    Jt(0,0) =                2.0f * (d.y() * q.z() - d.z() * q.y());               Jt(0,1) =                2.0f * (d.z() * q.x() - d.x() * q.z());              Jt(0,2) =                2.0f * (d.x() * q.y() - d.y() * q.x());
    Jt(1,0) =                2.0f * (d.y() * q.y() + d.z() * q.z());               Jt(1,1) = 2.0f * d.x() * q.y() - 4.0f * d.y() * q.x() + 2.0f * d.z() * q.w(); Jt(1,2) =  2.0f * d.x() * q.z() - 4.0f * d.z() * q.x() - 2.0f * d.y() * q.w();
    Jt(2,0) =  2.0f * d.y() * q.x() - 4.0f * d.x() * q.y() - 2.0f * d.z() * q.w(); Jt(2,1) =                2.0f * (d.x() * q.x() + d.z() * q.z());              Jt(2,2) =  2.0f * d.x() * q.w() - 4.0f * d.z() * q.y() + 2.0f * d.y() * q.z();
    Jt(3,0) =  2.0f * d.y() * q.w() - 4.0f * d.x() * q.z() + 2.0f * d.z() * q.x(); Jt(3,1) = 2.0f * d.z() * q.y() - 4.0f * d.y() * q.z() - 2.0f * d.x() * q.w(); Jt(3,2) =                2.0f * (d.x() * q.x() + d.y() * q.y());
    return Jt;
}

// Function to compute one filter iteration
void filterUpdate(Vector<3> gyro, Vector<3> accel, Vector<3> mag) {
    // local system variables
    const Vector<3> Ae{0.0,1.0,0.0};
    static Vector<3> Me{0.105,-0.545,-0.109}, gyroB{0.0,0.0,0.0}, gyroDrift{0,0,0};
    double beta;
    beta = gyroMeasError/3.0f;
    Quaternion<> dqFromGyro, dqFromAccelMag;//, qFromAccel, qFromMag;
    Vector<3> gyroError;

    static int count = 0;

    static systime_t oldTime = chVTGetSystemTime();

    double dt = ST2MS(chVTGetSystemTime() - oldTime)/1000.0f;
    oldTime = chVTGetSystemTime();

//    zeta(0) = 0.157f/30.0f;
//    zeta(1) = 0.157f/30.0f;
//    zeta(2) = 0.157f/30.0f;

    if( count < 25 ) {
        zeta(0) = 0.157f;
        zeta(1) = 0.157f;
        zeta(2) = 0.157f;
        beta = 30.0f * gyroMeasError;
        gyroDrift = gyroDrift + gyro;
        count++;

    } else if( count == 25 ) {
        zeta = (gyroDrift/25.0f)*sqrt(3.0f/4.0f);
        beta = gyroMeasError*sqrt(3.0f/4.0f);
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

    // compute the quaternion from gravity field oreentation
    std::function< Vector<6>( Vector<4>) > f = ([&] (Vector<4> q) -> Vector<6> {
        Vector<3> fromAccel = (Quaternion<>(q).conjugated() * Ae * Quaternion<>(q)).vector() - accel;
        Vector<3> fromMag = (Quaternion<>(q).conjugated() * Me * Quaternion<>(q)).vector() - mag;
        return Vector<6>{ fromAccel(0), fromAccel(1), fromAccel(2), fromMag(0), fromMag(1), fromMag(2) };
    });
    dqFromAccelMag = jacobian(f, (Vector<4>)q).transponced() * f(q);
    dqFromAccelMag.normalize();

    // compute angular estimated direction of the gyroscope error
    gyroError = (q.conjugated() * dqFromAccelMag).vector()*2.0f;
    // compute and remove the gyroscope baises
    gyroB = gyroB + gyroError * zeta;
    gyro = gyro - gyroB;

    // compute the quaternion rate measured by gyroscopes
    dqFromGyro = (q * Quaternion<>(0,gyro))*0.5f;

    // compute then integrate the estimated quaternion rate
    q = q + (dqFromGyro - (beta * dqFromAccelMag)) * dt;
    // normalise quaternion
    q.normalize();
    // compute flux in the earth frame
    Me = (q * mag * q.conjugated()).vector();

}

THD_FUNCTION(update, arg) {
    systime_t chibios_time = chVTGetSystemTime();
    Vector<3> gyro, accel, mag;
    Quaternion<> dq;
    Vector<3> gyroError;

    int count = 0;
    while( !chThdShouldTerminateX() ) {
//        chibios_time += MS2ST(NAV_UPDATE_PERIOD_MS);

        static systime_t oldTime = chVTGetSystemTime();

        double dt = ST2MS(chVTGetSystemTime() - oldTime)/1000.0f;
        oldTime = chVTGetSystemTime();

        gyro = {imuGyroGet().x, imuGyroGet().y, imuGyroGet().z};
        gyro = (M_PI/180.0f) * gyro;
        accel = {imuAccelGet().x, imuAccelGet().y, imuAccelGet().z};
        mag = {imuMagGet().x, imuMagGet().y, imuMagGet().z};

//        if( count < 25 ) {
//            gyroDrift = gyroDrift + gyro;
//            count++;

              accel.normalize();
              mag.normalize();

//            std::function< Vector<6>( Vector<4>) > f = ([&] (Vector<4> q) -> Vector<6> {
//                Vector<3> fromAccel = (Quaternion<>(q).conjugated() * Ae * Quaternion<>(q)).vector() - accel;
//                Vector<3> fromMag = (Quaternion<>(q).conjugated() * Me * Quaternion<>(q)).vector() - mag;
//                return Vector<6>{ fromAccel(0), fromAccel(1), fromAccel(2), fromMag(0), fromMag(1), fromMag(2) };
//            });
//            dq = jacobian(f, (Vector<4>)q).transponced() * f(q);
//            dq.normalize();
//            q = q + (((6.0f / 180.0f) * M_PI)/3.0f * dq) * dt;
//        } else if( count == 25 ) {
//            zeta = gyroDrift/25.0f;
//        } else {
            chBSemWait(&dataAccess);
            filterUpdate(gyro, accel, mag);
            chBSemSignal(&dataAccess);
    //    }


        //углы Эйлера в радианах
//        chBSemWait(&dataAccess);
//        rpy.time = chVTGetSystemTime();
//        rpy.x = atan2(2*(q.w()*q.x() + q.y()*q.z()), 1 - 2*(q.x()*q.x() + q.y()*q.y()));
//        rpy.y = asin(2*(q.w()*q.y() - q.z()*q.x()));
//        rpy.z = atan2(2*(q.w()*q.z() + q.x()*q.y()), 1 - 2*(q.y()*q.y() + q.z()*q.z()));
//        chBSemSignal(&dataAccess);

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
    vectorData ret = {0,0,0,0};
    chBSemWait(&dataAccess);
    ret.time = rpy.time;
    ret.x = rpy.x;
    ret.y = rpy.y;
    ret.z = rpy.z;
    chBSemSignal(&dataAccess);
    return ret;
}
