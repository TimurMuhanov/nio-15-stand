#include "nav.h"
#include "io.h"
#include <math.h>

#define gyroMeasError (M_PI * (6.0f / 180.0f)) // gyroscope measurement error in rad/s (shown as 5 deg/s)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError // compute beta
#define deltat (NAV_UPDATE_PERIOD_MS / 1000.0f)

static binary_semaphore_t dataAccess;
quaternionData SEq; //кватернион текущего положения
vectorData rpy;

static THD_FUNCTION(navUpdate, arg);
static THD_WORKING_AREA(navUpdateWorkingArea, 128);

void navInit(void){
	chBSemObjectInit(&dataAccess, false);

    chThdCreateStatic(  navUpdateWorkingArea,
                        sizeof(navUpdateWorkingArea),
                        NORMALPRIO, navUpdate, NULL);
}

scalarData Vect_abs(vectorData data){
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

/*quaternionData q_mult_q(quaternionData a, quaternionData b){
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
*/
quaternionData q_mult_v(quaternionData a, vectorData b){
        quaternionData res;
        res.w = -a.x * b.x - a.y * b.y - a.z * b.z;
        res.x = a.w * b.x + a.y * b.z - a.z * b.y;
        res.y = a.w * b.y - a.x * b.z + a.z * b.x;
        res.z = a.w * b.z + a.x * b.y - a.y * b.x;
        return res;
}


void filterUpdate(vectorData gyro, vectorData accel){
    // Local system variables
    quaternionData SEqDot_omega; // quaternion derrivative from gyroscopes
    vectorData f; // objective function
    float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33; // objective function Jacobian elements
    quaternionData SEqHatDot; // estimated direction of the gyroscope error
    quaternionData halfSEq;
    // Normalise the accelerometer measurement
    accel = Vect_norm(accel);
    // Compute the objective function and Jacobian

	f.x = 2.0f * SEq.x * SEq.z - 2.0f * SEq.w * SEq.y - accel.x;
    f.y = 2.0f * SEq.w * SEq.x + 2.0f * SEq.y * SEq.z - accel.y;
    f.z = 1.0f - 2.0f * SEq.x * SEq.x - 2.0f * SEq.y * SEq.y - accel.z;
    J_11or24 = 2.0f * SEq.y; // J_11 negated in matrix multiplication
    J_12or23 = 2.0f * SEq.z;
    J_13or22 = 2.0f * SEq.w; // J_12 negated in matrix multiplication
    J_14or21 = 2.0f * SEq.x;
    J_32 = 2.0f * J_14or21; // negated in matrix multiplication
    J_33 = 2.0f * J_11or24; // negated in matrix multiplication
    // Compute the gradient (matrix multiplication)
    SEqHatDot.w = J_14or21 * f.y - J_11or24 * f.x;
    SEqHatDot.x = J_12or23 * f.x + J_13or22 * f.y - J_32 * f.z;
    SEqHatDot.y = J_12or23 * f.y - J_33 * f.z - J_13or22 * f.x;
    SEqHatDot.z = J_14or21 * f.x + J_11or24 * f.y;
    // Normalise the gradient
    SEqHatDot = Quat_norm(SEqHatDot);
    // Compute the quaternion derrivative measured by gyroscopes
    halfSEq.w = 0.5f * SEq.w;
    halfSEq.x = 0.5f * SEq.x;
    halfSEq.y = 0.5f * SEq.y;
    halfSEq.z = 0.5f * SEq.z;
    SEqDot_omega = q_mult_v(halfSEq, gyro);
    // Compute then integrate the estimated quaternion derrivative
    SEq.w += (SEqDot_omega.w - (beta * SEqHatDot.w)) * deltat;
    SEq.x += (SEqDot_omega.x - (beta * SEqHatDot.x)) * deltat;
    SEq.y += (SEqDot_omega.y - (beta * SEqHatDot.y)) * deltat;
    SEq.z += (SEqDot_omega.z - (beta * SEqHatDot.z)) * deltat;
    // Normalise quaternion
    SEq = Quat_norm(SEq);
	SEq.time = gyro.time;
}

THD_FUNCTION(navUpdate, arg) {
	systime_t chibios_time = chVTGetSystemTime();

    SEq.w = 1;
    SEq.x = 0;
    SEq.y = 0;
    SEq.z = 0;
    SEq.time = 0;

    float phi, teta, psi;
    int presc = 0;

    vectorData accel, gyro;

	while(1) {
		chibios_time += MS2ST(NAV_UPDATE_PERIOD_MS);

        //измерения
        gyro = imuGyroGet();
        accel = imuAccelGet();
        gyro.x = ((M_PI/180) * gyro.x);
        gyro.y = ((M_PI/180) * gyro.y);
        gyro.z = ((M_PI/180) * gyro.z);

        filterUpdate(gyro, accel);

        //углы Эйлера в радианах
		chBSemWait(&dataAccess);
		rpy.x = atan2(2*(SEq.w*SEq.x + SEq.y*SEq.z), 1 - 2*(SEq.x*SEq.x + SEq.y*SEq.y));
		rpy.y = -asin(2*(SEq.w*SEq.y - SEq.z*SEq.x));
		rpy.z = atan2(2*(SEq.w*SEq.z + SEq.x*SEq.y), 1 - 2*(SEq.y*SEq.y + SEq.z*SEq.z));
		chBSemSignal(&dataAccess);

		chThdSleepUntil(chibios_time);
    }
}

quaternionData get_quat(void) {
	quaternionData ret = {0,0,0,0,0};
	chBSemWait(&dataAccess);
	ret.time = SEq.time;
	ret.w = SEq.w;
	ret.x = SEq.x;
	ret.y = SEq.y;
	ret.z = SEq.z;
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
