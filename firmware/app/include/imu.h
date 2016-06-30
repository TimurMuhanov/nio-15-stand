/**	@defgroup	IMU
	@author		Zaripov Kamil
				Inertial Measurement Unit
	@{ */
	
#ifndef IMU_H
#define IMU_H


#include "ch.hpp"
#include "PubSub.h"
#include "g_matrix.h"
#include "g_vector.h"
#include "g_quaternion.h"
#include <string>

#define M_PI           3.14159265358979323846

#define gyroMeasError ((6.0f / 180.0f) * M_PI) // gyroscope measurement error in rad/s (shown as 6 deg/s)
#define gyroMeasDrift ((0.3f / 180.0f) * M_PI) // gyroscope measurement error in rad/s/s (shown as 0.3f deg/s/s)

#define beta (sqrt(3.0f / 4.0f) * gyroMeasError) // compute beta
#define zeta (sqrt(3.0f / 4.0f) * gyroMeasDrift) // compute zeta

#define RAD_DEG(rad) (rad/M_PI*180)
#define DEG_RAD(deg) (deg/180*M_PI)
#define zeta (sqrt(3.0f / 4.0f) * gyroMeasDrift) // compute zeta

using namespace geometry;
using namespace chibios_rt;


#define CALIBRATE_STEPS         200


class ImuCalibrator : public BaseStaticThread<6000> {
    public:
                                            ImuCalibrator();
                                           ~ImuCalibrator();

        /** thread-safe */
        void                                startMagCalibration();
        /** thread-safe */
        void                                stopMagCalibration();
    private:
        virtual void                        main(void);

        Vector<3>                           magOffset{.0f, .0f, .0f}, magScale{1.0f, 1.0f, 1.0f};
        Vector<3>                           gyroOffset{.0f, .0f, .0f}, gyroScale{1.0f, 1.0f, 1.0f};
        Quaternion<>                        magAxis;

        bool                                isMagCalibrating = false;
        bool                                startMagCalibrate = false;
        bool                                stopMagCalibrate = false;
        Mutex                               magCalibrateMutex;

        int                                 gyroCalibrationStep = 0;
};


class Imu : public BaseStaticThread<6000> {
                                            Imu();
                                           ~Imu();
    public:
        static Imu&                         instance() {
            static Imu instance;
            return instance;
        }

        static Topic<vectorData>            accel;
        static Topic<vectorData>            gyro;
        static Topic<vectorData>            mag;
        static ImuCalibrator&               calibrator() {
            return instance()._calibrator;
        }
        static quaternionData               getQuat(){
            instance()._m.lock();
            quaternionData tmp =  instance().qData;
            instance()._m.unlock();
            return tmp;
        }

    private:
        virtual void                        main(void);
        Quaternion<>                        q_Earth_to_Frame(Vector<3> i_Earth_in_Frame, Vector<3> j_Earth_in_Frame);
        Quaternion<>                        q;
        quaternionData                      qData;
        ImuCalibrator                       _calibrator;
        Mutex                               _m;
};




#endif

/** @} */

