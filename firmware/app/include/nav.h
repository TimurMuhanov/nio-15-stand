/**	@defgroup	NAV
	@author		Agafonov Vladimir
				Navigation
	@{ */
#ifndef NAV_H
#define NAV_H


#include "ch.h"
#include "imu.h"
#include "thread.h"

#define NAV_UPDATE_PERIOD_MS 100
#define M_PI 3.1415

typedef struct {
	float w;
	float x;
	float y;
	float z;
	u32 time;			// us
} quaternionData;


#ifdef __cplusplus
extern "C" {
#endif

	//init nav
	void navInit(void);
	scalarData Vect_abs(vectorData data); //модуль вектора
	scalarData Quat_abs(quaternionData data);//модуль кватерниона
	vectorData Vect_norm(vectorData data); //нормировка вектора
	quaternionData Quat_norm(quaternionData data);//нормировка кватерниона
	//quaternionData q_mult_q(quaternionData q1, quaternionData q2); //умножение кватернионов
	quaternionData q_mult_v(quaternionData a, vectorData b); //умножение кватерниона на вектор
	//quaternionData q_invert(quaternionData q); //cопряженный кватернион
	//vectorData v_transform(quaternionData q, vectorData v); //поворот вектора кватернионом
	void filterUpdate(vectorData gyro, vectorData accel);
	quaternionData		get_quat(void);
	vectorData			get_rpy(void);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
