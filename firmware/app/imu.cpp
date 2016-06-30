#include "imu.h"
#include "adis16488.h"
#include "Terminal.h"
#include "Thread.h"
#include "Settings.h"
#include "Connection.h"
#include "Log.h"
#include "Encoder.h"

#define MODIFIED

#ifdef MODIFIED
Quaternion<> qFromGyro, qFromAccelMag, qAccelDirectoin, qMagDirection, qDirection, qTmp, qNew;

Vector<3> Ae{0, 1, 0};          // gravity field direction in the earth frame
Vector<3> Me{1, 0, 0};          // flux in the earh frame
Vector<3> gyroDrift{0, 0, 0}, gyroB{0, 0, 0};
Vector<3> magMean{0, 0, 0};
Vector<3> magAcc{0, 0, 0};
Vector<3> magOut{0, 0, 0};
Vector<3> accelAcc{0, 0, 0};
Vector<3> accelOut{0, 0, 0};

Matrix<4,3> jA, jM;
Vector<3> fA, fM;
Vector<3> fANew, fMNew;

float mergeCoeff = 0.9f;
#endif

vectorData gData;
vectorData aData;
vectorData mData;
Vector<3> i,j;

#ifndef MODIFIED
#define deltat 0.001f // sampling period in seconds (shown as 1 ms)
#define gyroMeasError 3.14159265358979 * (5.0f / 180.0f) // gyroscope measurement error in rad/s (shown as 5 deg/s)
#define gyroMeasDrift 3.14159265358979 * (0.2f / 180.0f) // gyroscope measurement error in rad/s/s (shown as 0.2f deg/s/s)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError // compute beta
#define zeta sqrt(3.0f / 4.0f) * gyroMeasDrift // compute zeta
// Global system variables
float a_x, a_y, a_z; // accelerometer measurements
float w_x, w_y, w_z; // gyroscope measurements in rad/s
float m_x, m_y, m_z; // magnetometer measurements
float SEq_1 = 1, SEq_2 = 0, SEq_3 = 0, SEq_4 = 0; // estimated orientation quaternion elements with initial conditions
float b_x = 1, b_z = 0; // reference direction of flux in earth frame
float w_bx = 0, w_by = 0, w_bz = 0; // estimate gyroscope biases error
Vector<3> Me{1, 0, 0};
#endif

Topic<vectorData> Imu::accel;
Topic<vectorData> Imu::gyro;
Topic<vectorData> Imu::mag;


Imu::Imu() {
    start(NORMALPRIO);
}

Imu::~Imu() {
}

void Imu::main() {
    setName( "Imu" );

    gData = Imu::gyro.get();
    aData = Imu::accel.get();
    mData = Imu::mag.get();

    Vector<3> gyro = gData.val;
    Vector<3> accel = aData.val;
    Vector<3> mag = mData.val;

    accel.normalize();
    mag.normalize();

    j = accel;
    i = (mag - j * (mag * j)).normalized();
    q = q_Earth_to_Frame(i, j);


    #ifdef MODIFIED
    Me = (q * mag * q.conjugated()).vector();
    #endif


    bool isRotated = false;
    bool isEncoderOffsetSet = false;
    while( !shouldTerminate() ) {
        gData = Imu::gyro.get();
        aData = Imu::accel.get();
        mData = Imu::mag.get();

        static systime_t oldTime = chVTGetSystemTime();
        float dt = ST2US(chVTGetSystemTime() - oldTime)/1.0e6f;
        oldTime = chVTGetSystemTime();

        if( ST2S(gData.time)>5 && !isRotated ) {
            isRotated = true;

            double yaw = atan2f( 2*(q.w()*q.y() - q.x()*q.z()), 2*q.w()*q.w() + 2*q.x()*q.x() - 1 );
            q = Quaternion<>{ cosf(-yaw/2), 0, sinf(-yaw/2), 0 } * q;

            Me = (q * mag * q.conjugated()).vector();
        }

        if( ST2S(gData.time)>10 && !isEncoderOffsetSet ) {
            isEncoderOffsetSet = true;
            Vector<3> Euler, Sharnear;
/* gamma */ Euler(0) = atan2f( 2*(q.w()*q.x() - q.y()*q.z()), 2*q.w()*q.w() + 2*q.y()*q.y() - 1 );
/* theta */ Euler(1) = asinf( 2*(q.x()*q.y() + q.z()*q.w()) );
/* psi */   Euler(2) = atan2f( 2*(q.w()*q.y() - q.x()*q.z()), 2*q.w()*q.w() + 2*q.x()*q.x() - 1 );
            Sharnear(1) = acosf(cosf(Euler(1)) * cosf(Euler(2)));
            Sharnear(2) = atan2f(-sinf(Euler(2)), tanf(Euler(1)));
            Sharnear(0) = asinf((cosf(Euler(0)) * sinf(Euler(2)) + cosf(Euler(2)) * sinf(Euler(1)) * sinf(Euler(0)))/sinf(Sharnear(1)));
            //Sharnear(0) = Euler(0);
            //Sharnear(1) = Euler(1);
           // Sharnear(2) = Euler(2);
            encoderSetOffset(0, RAD_DEG(Sharnear(0)));
            encoderSetOffset(1, RAD_DEG(Sharnear(1)));
            encoderSetOffset(2, RAD_DEG(Sharnear(2)));
        }

        palSetPad(GPIOC, 0);

        gyro = DEG_RAD(gData.val);
        accel = aData.val;
        mag = mData.val;

        accel.normalize();
        mag.normalize();

#ifdef MODIFIED

        float oldError, newError;
        int s=0;
        qFromAccelMag = q + q * gyro * 0.5f * dt;
        do {
            jA(0,0) =                2.0f * (Ae.y() * qFromAccelMag.z() - Ae.z() * qFromAccelMag.y());                jA(0,1) =                2.0f * (Ae.z() * qFromAccelMag.x() - Ae.x() * qFromAccelMag.z());               jA(0,2) =                2.0f * (Ae.x() * qFromAccelMag.y() - Ae.y() * qFromAccelMag.x());
            jA(1,0) =                2.0f * (Ae.y() * qFromAccelMag.y() + Ae.z() * qFromAccelMag.z());                jA(1,1) = 2.0f * Ae.x() * qFromAccelMag.y() - 4.0f * Ae.y() * qFromAccelMag.x() + 2.0f * Ae.z() * qFromAccelMag.w(); jA(1,2) =  2.0f * Ae.x() * qFromAccelMag.z() - 4.0f * Ae.z() * qFromAccelMag.x() - 2.0f * Ae.y() * qFromAccelMag.w();
            jA(2,0) =  2.0f * Ae.y() * qFromAccelMag.x() - 4.0f * Ae.x() * qFromAccelMag.y() - 2.0f * Ae.z() * qFromAccelMag.w(); jA(2,1) =                2.0f * (Ae.x() * qFromAccelMag.x() + Ae.z() * qFromAccelMag.z());               jA(2,2) =  2.0f * Ae.x() * qFromAccelMag.w() - 4.0f * Ae.z() * qFromAccelMag.y() + 2.0f * Ae.y() * qFromAccelMag.z();
            jA(3,0) =  2.0f * Ae.y() * qFromAccelMag.w() - 4.0f * Ae.x() * qFromAccelMag.z() + 2.0f * Ae.z() * qFromAccelMag.x(); jA(3,1) = 2.0f * Ae.z() * qFromAccelMag.y() - 4.0f * Ae.y() * qFromAccelMag.z() - 2.0f * Ae.x() * qFromAccelMag.w(); jA(3,2) =                2.0f * (Ae.x() * qFromAccelMag.x() + Ae.y() * qFromAccelMag.y());

            fA = (qFromAccelMag.conjugated() * Ae * qFromAccelMag).vector() - accel;
//            fA = (qFromAccelMag * Ae * qFromAccelMag.conjugated()).vector() - accel;
            qAccelDirectoin = jA * fA;

            jM(0,0) =                2.0f * (Me.y() * qFromAccelMag.z() - Me.z() * qFromAccelMag.y());               jM(0,1) =                2.0f * (Me.z() * qFromAccelMag.x() - Me.x() * qFromAccelMag.z());              jM(0,2) =                2.0f * (Me.x() * qFromAccelMag.y() - Me.y() * qFromAccelMag.x());
            jM(1,0) =                2.0f * (Me.y() * qFromAccelMag.y() + Me.z() * qFromAccelMag.z());               jM(1,1) = 2.0f * Me.x() * qFromAccelMag.y() - 4.0f * Me.y() * qFromAccelMag.x() + 2.0f * Me.z() * qFromAccelMag.w(); jM(1,2) =  2.0f * Me.x() * qFromAccelMag.z() - 4.0f * Me.z() * qFromAccelMag.x() - 2.0f * Me.y() * qFromAccelMag.w();
            jM(2,0) =  2.0f * Me.y() * qFromAccelMag.x() - 4.0f * Me.x() * qFromAccelMag.y() - 2.0f * Me.z() * qFromAccelMag.w(); jM(2,1) =                2.0f * (Me.x() * qFromAccelMag.x() + Me.z() * qFromAccelMag.z());              jM(2,2) =  2.0f * Me.x() * qFromAccelMag.w() - 4.0f * Me.z() * qFromAccelMag.y() + 2.0f * Me.y() * qFromAccelMag.z();
            jM(3,0) =  2.0f * Me.y() * qFromAccelMag.w() - 4.0f * Me.x() * qFromAccelMag.z() + 2.0f * Me.z() * qFromAccelMag.x(); jM(3,1) = 2.0f * Me.z() * qFromAccelMag.y() - 4.0f * Me.y() * qFromAccelMag.z() - 2.0f * Me.x() * qFromAccelMag.w(); jM(3,2) =                2.0f * (Me.x() * qFromAccelMag.x() + Me.y() * qFromAccelMag.y());

            fM = (qFromAccelMag.conjugated() * Me * qFromAccelMag).vector() - mag;
//            fM = (qFromAccelMag * Me * qFromAccelMag.conjugated()).vector() - mag;
            qMagDirection = jM * fM;

            oldError = sqrtf( powf(fA.norm(),2) + powf(fM.norm(),2) );
//
//            qDirection = (qAccelDirectoin + qMagDirection).normalized();

            if( !( (aData.val.norm() > 0.997f) && (aData.val.norm() < 1.003f) ) ) {
                qAccelDirectoin = Quaternion<>{0,0,0,0};
            }

            if( !( (mData.val.norm() > 0.455f) && (mData.val.norm() < 0.461f) ) ) {
                qMagDirection = Quaternion<>{0,0,0,0};
            }
//            qAccelDirectoin = qAccelDirectoin*expf( powf( aData.val.norm() - 1.0f, 2 )/0.0005 );
//            qMagDirection = qMagDirection*expf( powf( mData.val.norm() - 0.458f, 2 )/0.0005 );

            qDirection = (qAccelDirectoin + qMagDirection).normalized();
            float step = 5.0e-3;

            int subStep = 0;
            do {
                qNew = qFromAccelMag - step*qDirection;
                qNew.normalize();
                fANew = (qNew.conjugated() * Ae * qNew).vector() - accel;
                fMNew = (qNew.conjugated() * Me * qNew).vector() - mag;
//                fANew = (qNew * Ae * qNew.conjugated()).vector() - accel;
//                fMNew = (qNew * Me * qNew.conjugated()).vector() - mag;
                newError = sqrtf( powf(fANew.norm(),2) + powf(fMNew.norm(),2) );

//                Terminal::print("\tstep: %.6f new %.6f; %d\n\r", oldError, newError, subStep);

                step /= 2.0f;
            } while( newError >= oldError && ++subStep<10 );

            if(  newError < oldError ) {
                qFromAccelMag = qNew;
            }

//            Terminal::print("old: %.6f new %.6f; %d\n\r", oldError, newError, s);

        } while( newError < oldError && ++s<10 );

        qFromGyro = q + q * gyro * 0.5f*dt;


        q = mergeCoeff*qFromGyro + (1.0f-mergeCoeff)*qFromAccelMag;
        q.normalize();

//        Connection::instance().valueSend(gData.time, "blah", 10.0f);

        Vector<3> ht = (q * mag * q.conjugated()).vector();
        Me(1) = ht(1);
        Me.normalize();
//        Me = Vector<3>{ sqrtf( powf(ht(0),2) + powf(ht(2),2) ), ht(1), 0 };
#endif
#ifndef MODIFIED
        const Vector<3> Ae{0, 1, 0};
        static Vector<3> gyroB{0.0, 0.0, 0.0};
        Quaternion<> qPre, qFromGyro, qFromAccelMag;
        Vector<3> gyroError;

        //static systime_t oldTime = chVTGetSystemTime();
        //float dt = ST2US(chVTGetSystemTime() - oldTime)/1.0e6f;
        oldTime = chVTGetSystemTime();

        qPre = (q * Quaternion<>(0,gyro))*0.5f;

        // compute flux in the earth frame
        //mag = (qPre * mag * qPre.conjugated()).vector();
       // mag(1) = 0;
        //mag = (qPre.conjugated() * mag * qPre).vector();
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

        //q = Quaternion<>{SEq_1, SEq_2, SEq_3, SEq_4};
#endif

        palClearPad(GPIOC, 0);

        _m.lock();
        qData.time = gData.time;
        qData.val = q;
        _m.unlock();
    }
}

Quaternion<> Imu::q_Earth_to_Frame(Vector<3> i_Earth_in_Frame, Vector<3> j_Earth_in_Frame) {
    Vector<3> r1 = i_Earth_in_Frame - Vector<3>{1.0, 0.0, 0.0};
    Vector<3> r2 = j_Earth_in_Frame - Vector<3>{0.0, 1.0, 0.0};
    Vector<3> s2 = j_Earth_in_Frame + Vector<3>{0.0, 1.0, 0.0};
    Quaternion<> returnQuaternion;
    returnQuaternion.scalar() = r1 * s2;
    returnQuaternion.vector() = r2 ^ r1;
    return returnQuaternion.normalized();
}




ImuCalibrator::ImuCalibrator() {
    if( Settings::contains("IMU_MAG_OFFSET_0") &&
        Settings::contains("IMU_MAG_OFFSET_1") &&
        Settings::contains("IMU_MAG_OFFSET_2") &&
        Settings::contains("IMU_MAG_SCALE_0") &&
        Settings::contains("IMU_MAG_SCALE_1") &&
        Settings::contains("IMU_MAG_SCALE_2") )
    {
        magOffset(0) = std::stof( Settings::get("IMU_MAG_OFFSET_0") );
        magOffset(1) = std::stof( Settings::get("IMU_MAG_OFFSET_1") );
        magOffset(2) = std::stof( Settings::get("IMU_MAG_OFFSET_2") );
        magScale(0) = std::stof( Settings::get("IMU_MAG_SCALE_0") );
        magScale(1) = std::stof( Settings::get("IMU_MAG_SCALE_1") );
        magScale(2) = std::stof( Settings::get("IMU_MAG_SCALE_2") );
    }

    start(NORMALPRIO);
}

ImuCalibrator::~ImuCalibrator() {
}

void ImuCalibrator::startMagCalibration() {
    magCalibrateMutex.lock();
    startMagCalibrate = true;
    magCalibrateMutex.unlock();
}

void ImuCalibrator::stopMagCalibration() {
    magCalibrateMutex.lock();
    stopMagCalibrate = true;
    magCalibrateMutex.unlock();
}

Matrix<4,3> Jt_E(Quaternion<> q, Vector<3> d){
    Matrix<4,3> Jt;
    Jt(0,0) =                2.0f * (d.y() * q.z() - d.z() * q.y());               Jt(0,1) =                2.0f * (d.z() * q.x() - d.x() * q.z());              Jt(0,2) =                2.0f * (d.x() * q.y() - d.y() * q.x());
    Jt(1,0) =                2.0f * (d.y() * q.y() + d.z() * q.z());               Jt(1,1) = 2.0f * d.x() * q.y() - 4.0f * d.y() * q.x() + 2.0f * d.z() * q.w(); Jt(1,2) =  2.0f * d.x() * q.z() - 4.0f * d.z() * q.x() - 2.0f * d.y() * q.w();
    Jt(2,0) =  2.0f * d.y() * q.x() - 4.0f * d.x() * q.y() - 2.0f * d.z() * q.w(); Jt(2,1) =                2.0f * (d.x() * q.x() + d.z() * q.z());              Jt(2,2) =  2.0f * d.x() * q.w() - 4.0f * d.z() * q.y() + 2.0f * d.y() * q.z();
    Jt(3,0) =  2.0f * d.y() * q.w() - 4.0f * d.x() * q.z() + 2.0f * d.z() * q.x(); Jt(3,1) = 2.0f * d.z() * q.y() - 4.0f * d.y() * q.z() - 2.0f * d.x() * q.w(); Jt(3,2) =                2.0f * (d.x() * q.x() + d.y() * q.y());
    return Jt;
}

void ImuCalibrator::main() {
    setName( "Imu calibrator" );
    vectorData mData = Adis::mag.get();
    Vector<3> min = mData.val, max = mData.val;//, longAxis{0.0,0.0,0.0},shortAxis = mData.val, middleAxis{0.0,0.0,0.0};

    vectorData gData = Adis::gyro.get();
    vectorData aData = Adis::accel.get();
//    static int step = 0;
    while( !shouldTerminate() ) {
        gData = Adis::gyro.get();
        aData = Adis::accel.get();
        mData = Adis::mag.get();

        // gyro calibration
        if( gyroCalibrationStep < CALIBRATE_STEPS ) {
            gyroOffset = gyroOffset + gData.val;
            ++gyroCalibrationStep;

        } else if( gyroCalibrationStep == CALIBRATE_STEPS ) {
            gyroOffset = -1*gyroOffset/CALIBRATE_STEPS;
            ++gyroCalibrationStep;
        }


        // magCalibration
        magCalibrateMutex.lock();
        if( startMagCalibrate ) {
            startMagCalibrate = false;
            isMagCalibrating = true;
//            Terminal::print("mag cal start\n\r");
        }
        magCalibrateMutex.unlock();

        if( isMagCalibrating ) {
            for(int j=0; j<3 ; j++){
                if(min(j) > mData.val(j)) min(j) = mData.val(j);
                if(max(j) < mData.val(j)) max(j) = mData.val(j);
            }
        }

        magCalibrateMutex.lock();
        if( stopMagCalibrate ) {
            stopMagCalibrate = false;

            if( isMagCalibrating ) {
                isMagCalibrating = false;

//                Terminal::print("mag cal stop\n\r");

                magOffset = (min + max)/2;

                float maxScale = 0;
                for(int i=0; i<3; i++) {
                    if( maxScale < (max(i) - min(i)) )
                        maxScale = (max(i) - min(i));
                    magScale(i) = 1.0f/(max(i) - min(i));
                }
                magScale = magScale * maxScale;

                Settings::set("IMU_MAG_OFFSET_0", std::to_string( magOffset(0)));
                Settings::set("IMU_MAG_OFFSET_1", std::to_string( magOffset(1)));
                Settings::set("IMU_MAG_OFFSET_2", std::to_string( magOffset(2)));
                Settings::set("IMU_MAG_SCALE_0", std::to_string( magScale(0)));
                Settings::set("IMU_MAG_SCALE_1", std::to_string( magScale(1)));
                Settings::set("IMU_MAG_SCALE_2", std::to_string( magScale(2)));
                Settings::sync();

//                Terminal::print( "%f %f %f | %f %f %f\n\r", magOffset(0), magOffset(1), magOffset(2), magScale(0), magScale(1), magScale(2) );
            }
        }
        magCalibrateMutex.unlock();

        gData.val(0) = (gData.val(0)+gyroOffset(0))*gyroScale(0);
        gData.val(1) = (gData.val(1)+gyroOffset(1))*gyroScale(1);
        gData.val(2) = (gData.val(2)+gyroOffset(2))*gyroScale(2);

        mData.val(0) = ( mData.val(0) + magOffset(0) ) * magScale(0);
        mData.val(1) = ( mData.val(1) + magOffset(1) ) * magScale(1);
        mData.val(2) = ( mData.val(2) + magOffset(2) ) * magScale(2);


        Imu::gyro = gData;
        Imu::accel = aData;
        Imu::mag = mData;
    }
}



//    vectorData gData = Imu::instance()._gyro;
//    vectorData aData = Imu::instance()._accel;
//    vectorData mData = Imu::instance()._mag;

//    Vector<3> gyro = gData.val/180*3.1415;
//    Vector<3> accel = aData.val;
//    Vector<3> mag = mData.val;

//    static systime_t oldTime = chVTGetSystemTime();
//    float deltat = ST2US(chVTGetSystemTime() - oldTime)/1.0e6f;
//    oldTime = chVTGetSystemTime();


//    float a_x = accel(0), a_y = accel(2), a_z = -accel(1); // accelerometer measurements
//    float w_x = gyro(0), w_y = gyro(2), w_z = -gyro(1); // gyroscope measurements in rad/s
//    float m_x = mag(0), m_y = mag(2), m_z = -mag(1); // magnetometer measurements

//    float norm; // vector norm
//    float SEqDot_omega_1, SEqDot_omega_2, SEqDot_omega_3, SEqDot_omega_4; // quaternion rate from gyroscopes elements
//    float f_1, f_2, f_3, f_4, f_5, f_6; // objective function elements
//    float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33, // objective function Jacobian elements
//    J_41, J_42, J_43, J_44, J_51, J_52, J_53, J_54, J_61, J_62, J_63, J_64; //
//    float SEqHatDot_1, SEqHatDot_2, SEqHatDot_3, SEqHatDot_4; // estimated direction of the gyroscope error
//    float w_err_x, w_err_y, w_err_z; // estimated direction of the gyroscope error (angular)
//    float h_x, h_y, h_z; // computed flux in the earth frame
//    // axulirary variables to avoid reapeated calcualtions
//    float halfSEq_1 = 0.5f * SEq_1;
//    float halfSEq_2 = 0.5f * SEq_2;
//    float halfSEq_3 = 0.5f * SEq_3;
//    float halfSEq_4 = 0.5f * SEq_4;
//    float twoSEq_1 = 2.0f * SEq_1;
//    float twoSEq_2 = 2.0f * SEq_2;
//    float twoSEq_3 = 2.0f * SEq_3;
//    float twoSEq_4 = 2.0f * SEq_4;
//    float twob_x = 2.0f * b_x;
//    float twob_z = 2.0f * b_z;
//    float twob_xSEq_1 = 2.0f * b_x * SEq_1;
//    float twob_xSEq_2 = 2.0f * b_x * SEq_2;
//    float twob_xSEq_3 = 2.0f * b_x * SEq_3;
//    float twob_xSEq_4 = 2.0f * b_x * SEq_4;
//    float twob_zSEq_1 = 2.0f * b_z * SEq_1;
//    float twob_zSEq_2 = 2.0f * b_z * SEq_2;
//    float twob_zSEq_3 = 2.0f * b_z * SEq_3;
//    float twob_zSEq_4 = 2.0f * b_z * SEq_4;
//    float SEq_1SEq_2;
//    float SEq_1SEq_3 = SEq_1 * SEq_3;
//    float SEq_1SEq_4;
//    float SEq_2SEq_3;
//    float SEq_2SEq_4 = SEq_2 * SEq_4;
//    float SEq_3SEq_4;
//    float twom_x = 2.0f * m_x;
//    float twom_y = 2.0f * m_y;
//    float twom_z = 2.0f * m_z;
//    // normalise the accelerometer measurement
//    norm = sqrt(a_x * a_x + a_y * a_y + a_z * a_z);
//    a_x /= norm;
//    a_y /= norm;
//    a_z /= norm;
//    // normalise the magnetometer measurement
//    norm = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
//    m_x /= norm;
//    m_y /= norm;
//    m_z /= norm;
//    // compute the objective function and Jacobian
//    f_1 = twoSEq_2 * SEq_4 - twoSEq_1 * SEq_3 - a_x;
//    f_2 = twoSEq_1 * SEq_2 + twoSEq_3 * SEq_4 - a_y;
//    f_3 = 1.0f - twoSEq_2 * SEq_2 - twoSEq_3 * SEq_3 - a_z;
//    f_4 = twob_x * (0.5f - SEq_3 * SEq_3 - SEq_4 * SEq_4) + twob_z * (SEq_2SEq_4 - SEq_1SEq_3) - m_x;
//    f_5 = twob_x * (SEq_2 * SEq_3 - SEq_1 * SEq_4) + twob_z * (SEq_1 * SEq_2 + SEq_3 * SEq_4) - m_y;
//    f_6 = twob_x * (SEq_1SEq_3 + SEq_2SEq_4) + twob_z * (0.5f - SEq_2 * SEq_2 - SEq_3 * SEq_3) - m_z;
//    J_11or24 = twoSEq_3; // J_11 negated in matrix multiplication
//    J_12or23 = 2.0f * SEq_4;
//    J_13or22 = twoSEq_1; // J_12 negated in matrix multiplication
//    J_14or21 = twoSEq_2;
//    J_32 = 2.0f * J_14or21; // negated in matrix multiplication
//    J_33 = 2.0f * J_11or24; // negated in matrix multiplication
//    J_41 = twob_zSEq_3; // negated in matrix multiplication
//    J_42 = twob_zSEq_4;
//    J_43 = 2.0f * twob_xSEq_3 + twob_zSEq_1; // negated in matrix multiplication
//    J_44 = 2.0f * twob_xSEq_4 - twob_zSEq_2; // negated in matrix multiplication
//    J_51 = twob_xSEq_4 - twob_zSEq_2; // negated in matrix multiplication
//    J_52 = twob_xSEq_3 + twob_zSEq_1;
//    J_53 = twob_xSEq_2 + twob_zSEq_4;
//    J_54 = twob_xSEq_1 - twob_zSEq_3; // negated in matrix multiplication
//    J_61 = twob_xSEq_3;
//    J_62 = twob_xSEq_4 - 2.0f * twob_zSEq_2;
//    J_63 = twob_xSEq_1 - 2.0f * twob_zSEq_3;
//    J_64 = twob_xSEq_2;
//    // compute the gradient (matrix multiplication)
//    SEqHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1 - J_41 * f_4 - J_51 * f_5 + J_61 * f_6;
//    SEqHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3 + J_42 * f_4 + J_52 * f_5 + J_62 * f_6;
//    SEqHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1 - J_43 * f_4 + J_53 * f_5 + J_63 * f_6;
//    SEqHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2 - J_44 * f_4 - J_54 * f_5 + J_64 * f_6;
//    // normalise the gradient to estimate direction of the gyroscope error
//    norm = sqrt(SEqHatDot_1 * SEqHatDot_1 + SEqHatDot_2 * SEqHatDot_2 + SEqHatDot_3 * SEqHatDot_3 + SEqHatDot_4 * SEqHatDot_4);
//    SEqHatDot_1 = SEqHatDot_1 / norm;
//    SEqHatDot_2 = SEqHatDot_2 / norm;
//    SEqHatDot_3 = SEqHatDot_3 / norm;
//    SEqHatDot_4 = SEqHatDot_4 / norm;
//    // compute angular estimated direction of the gyroscope error
//    w_err_x = twoSEq_1 * SEqHatDot_2 - twoSEq_2 * SEqHatDot_1 - twoSEq_3 * SEqHatDot_4 + twoSEq_4 * SEqHatDot_3;
//    w_err_y = twoSEq_1 * SEqHatDot_3 + twoSEq_2 * SEqHatDot_4 - twoSEq_3 * SEqHatDot_1 - twoSEq_4 * SEqHatDot_2;
//    w_err_z = twoSEq_1 * SEqHatDot_4 - twoSEq_2 * SEqHatDot_3 + twoSEq_3 * SEqHatDot_2 - twoSEq_4 * SEqHatDot_1;
//    // compute and remove the gyroscope baises
//    w_bx += w_err_x * deltat * zeta;
//    w_by += w_err_y * deltat * zeta;
//    w_bz += w_err_z * deltat * zeta;
//    w_x -= w_bx;
//    w_y -= w_by;
//    w_z -= w_bz;
//    // compute the quaternion rate measured by gyroscopes
//    SEqDot_omega_1 = -halfSEq_2 * w_x - halfSEq_3 * w_y - halfSEq_4 * w_z;
//    SEqDot_omega_2 = halfSEq_1 * w_x + halfSEq_3 * w_z - halfSEq_4 * w_y;
//    SEqDot_omega_3 = halfSEq_1 * w_y - halfSEq_2 * w_z + halfSEq_4 * w_x;
//    SEqDot_omega_4 = halfSEq_1 * w_z + halfSEq_2 * w_y - halfSEq_3 * w_x;
//    // compute then integrate the estimated quaternion rate
//    SEq_1 += (SEqDot_omega_1 - (beta * SEqHatDot_1)) * deltat;
//    SEq_2 += (SEqDot_omega_2 - (beta * SEqHatDot_2)) * deltat;
//    SEq_3 += (SEqDot_omega_3 - (beta * SEqHatDot_3)) * deltat;
//    SEq_4 += (SEqDot_omega_4 - (beta * SEqHatDot_4)) * deltat;
//    // normalise quaternion
//    norm = sqrt(SEq_1 * SEq_1 + SEq_2 * SEq_2 + SEq_3 * SEq_3 + SEq_4 * SEq_4);
//    SEq_1 /= norm;
//    SEq_2 /= norm;
//    SEq_3 /= norm;
//    SEq_4 /= norm;
//    // compute flux in the earth frame
//    SEq_1SEq_2 = SEq_1 * SEq_2; // recompute axulirary variables
//    SEq_1SEq_3 = SEq_1 * SEq_3;
//    SEq_1SEq_4 = SEq_1 * SEq_4;
//    SEq_3SEq_4 = SEq_3 * SEq_4;
//    SEq_2SEq_3 = SEq_2 * SEq_3;
//    SEq_2SEq_4 = SEq_2 * SEq_4;
//    h_x = twom_x * (0.5f - SEq_3 * SEq_3 - SEq_4 * SEq_4) + twom_y * (SEq_2SEq_3 - SEq_1SEq_4) + twom_z * (SEq_2SEq_4 + SEq_1SEq_3);
//    h_y = twom_x * (SEq_2SEq_3 + SEq_1SEq_4) + twom_y * (0.5f - SEq_2 * SEq_2 - SEq_4 * SEq_4) + twom_z * (SEq_3SEq_4 - SEq_1SEq_2);
//    h_z = twom_x * (SEq_2SEq_4 - SEq_1SEq_3) + twom_y * (SEq_3SEq_4 + SEq_1SEq_2) + twom_z * (0.5f - SEq_2 * SEq_2 - SEq_3 * SEq_3);
//    // normalise the flux vector to have only components in the x and z
//    b_x = sqrt((h_x * h_x) + (h_y * h_y));
//    b_z = h_z;

//    quaternionData qD;
//    qD.time = gData.time;
//    qD.w = SEq_1;
//    qD.x = SEq_2;
//    qD.y = SEq_3;
//    qD.z = SEq_4;

//    vectorData rpy;
//    rpy.time = gData.time;
//    rpy.val(0) = atan2(2*(SEq_1*SEq_2 + SEq_3*SEq_4), 1 - 2*(SEq_2*SEq_2 + SEq_3*SEq_3));
//    rpy.val(1) = atan2(2*(SEq_1*SEq_4 + SEq_2*SEq_3), 1 - 2*(SEq_3*SEq_3 + SEq_4*SEq_4));
//    rpy.val(2) = asin(2*(SEq_1*SEq_3 - SEq_4*SEq_2));

//    static u32 cnt = 0;
//    if( cnt % 10 == 0 ) {
//        send(qD, gData, aData, mData, rpy);
//    }
//    cnt++;
