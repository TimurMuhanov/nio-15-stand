#include <math.h>
//#include <matrix.h>
#include "servo.h"
#include "encoder.h"

// Начальные смещения рулей [deg]
float vDelta_o[5]={0,-12,0,0,-12};

// Балансировочные углы - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// Время дискретизации [сек]
//float dt = 0.01;
// V = 25 m/s

// Aerleron - работает                  
//               teta  gamma  psi  wx    wy   wz
//float Kij[6][6]={{0,  1.12,  0.3,  0.11,  0.5,   0},   // servo #1 Aerleron right
//                 {0,  0.45,    0,  0.06, 0.01, 0.4},   // servo #2 Stabilizer right
//                 {0, -1.12, -0.3, -0.11, -0.5,   0},   // servo #3 Aerleron left
//                 {0, -1.08,-0.65, -0.08,-0.76,   0},   // servo #4 Rudder
//                 {0, -0.45,    0, -0.06,-0.01, 0.4},   // servo #5 Stabilizer left
//                 {0,     0,    0,     0,    0,   0}};  // servo #6 
                                 
//               teta  gamma  psi  wx    wy   wz
//float Kij[6][6]={{0,  2.33, 0.58,  0.22, 0.91,   0},   // servo #1 Aerleron right
//                 {0,  0.27,-0.07,  0.04, 0.00, 0.4},   // servo #2 Stabilizer right
//                 {0, -2.33,-0.58, -0.22,-0.91,   0},   // servo #3 Aerleron left
//                 {0, -0.84,-0.54, -0.05,-0.63,   0},   // servo #4 Rudder
//                 {0, -0.27, 0.07, -0.04,  0.0, 0.4},   // servo #5 Stabilizer left
//                 {0,     0,    0,     0,    0,   0}};  // servo #6 


// test
//               teta  gamma  psi  wx    wy   wz
float Kij[6][6]={{0,    1.6363,   -0.2754,    0.1451,    0.6002,         0},
		         {1,    1.1384,   -0.0611,    0.1183,    0.1975,    0.4000},
		         {0,   -1.6363,    0.2754,   -0.1451,   -0.6002,         0},
		         {0,   -1.7633,    0.5389,   -0.1320,   -0.9828,         0},
		         {1,   -1.1384,    0.0611,   -0.1183,   -0.1975,    0.4000},
		         {0,     0,    0,     0,    0,   0}};
// Число используемых в законе управления сервоприводов
int N=5; 
int secCount=0;
int firstStep=0;

// Вектор углового положения модели
float vStateVect [6] = {0,0,0,0,0,0};
float iDeltaStep [6] = {0.0,0.0,0.0,0.0,0.0,0.0};

int iLab = 0;

void process( void ) {
    int i;
    
    if(firstStep == 0) {
    	firstStep = 1;
	    for (i=0;i<6;i++){
	    	Kij[i][2] *= 1;    // psi
	    }
    }

    secCount++;
    // Подготовка вектора текущего состояния
    // Вектор углового положения модели: tetha, psi, gamma, omegax, omegay, omegaz
    // Запись текущего вектора положения модели по данным энкодеров
    vStateVect [0] = encoderGet(TETHA).val; // tetha
    vStateVect [1] = encoderGet(PSI).val;	// psi
    vStateVect [2] = encoderGet(GAMMA).val; //gamma
    // Запись угловых скоростей из инерциальной системы (после фильтра Калмана)
    vStateVect [3] = imuGyroGet().x; // omegax
    vStateVect [4] = imuGyroGet().y; // omegay
    vStateVect [5] = imuGyroGet().z; // omegaz
    // Stepwise stabilizer deflection
    if(iLab<8) {
    if (secCount > 2000) {
        iDeltaStep[1] = iDeltaStep[1]-2;
        iDeltaStep[4] = iDeltaStep[4]-2;
        secCount = 0;
        iLab = iLab+1;
    }
    }

    for (i=0;i<N;i++){
    	servoSet(i,	vDelta_o[i] +
					Kij[i][0]*(vStateVect [0] - vPHIo[0]) + //teta
					Kij[i][1]*(vStateVect [2] - vPHIo[1]) +  //gamma
					Kij[i][2]*(vStateVect [1] - vPHIo[2]) +  //psi
					Kij[i][3]*vStateVect [3] +               //wx
					Kij[i][4]*vStateVect [4] +               //wy
					Kij[i][5]*vStateVect [5] + iDeltaStep[i] );                //wz
    }
}
