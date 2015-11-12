#include <math.h>
#include <matrix.h>
//#include <stdlib.h>
//#include <stdio.h>
#include "servo.h"
#include "encoder.h"


// Начальные смещения рулей [deg]
float vDelta_o[5]={0,-12,0,0,-12};

// Балансировочные углы - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// Число используемых в законе управления сервоприводов
int N=6; 
                 
// Время дискретизации [сек]
float dt = 0.01;

// Число РБФ
//int I_NUMB_CENTR = 1;
//int I_NUMB_NN = 19; // =  (2*I_NUMB_CENTR+1)*6+1
//int I_NUMB_W  = 76; // = I_NUMB_NN*4/*
//int I_NUMB_CENTR = 3;
//int I_NUMB_NN = 43; // =  (2*I_NUMB_CENTR+1)*6+1
//int I_NUMB_W  = 172; // = I_NUMB_NN*4*/
//int I_NUMB_CENTR = 4;
//int I_NUMB_NN = 55; // =  (2*I_NUMB_CENTR+1)*6+1
//int I_NUMB_W  = 220; // = I_NUMB_NN*4*/
#define I_NUMB_CENTR	10
#define I_NUMB_NN		127		// =  (2*I_NUMB_CENTR+1)*6+1
#define I_NUMB_W 		508		// = I_NUMB_NN*4

//#define I_NUMB_CENTR 10
//#define I_NUMB_NN 127 // =  (2*I_NUMB_CENTR+1)*6+1
//#define I_NUMB_W  508 // = I_NUMB_NN*4

// Ширина шага при определении центров РБФ 
float vDelta [6] = {0.78, 3.14, 0.34, 2, 1, 0.3};

// Ширина шага при определении купола РБФ
//float vSigma [6] = {0.7170, 1.7133,0.1563, 0.5456, 0.4596, 0.0818};// I_NUMB_CENTR = 1;
//float vSigma [6] = {0.4998, 1.3320,0.1089, 0.4242, 0.3204, 0.0636};// I_NUMB_CENTR = 3;
//float vSigma [6] = {0.4526, 1.2396,0.0986, 0.3948, 0.2901, 0.0592};// I_NUMB_CENTR = 4;
float vSigma [6] = {0.3309, 0.9798, 0.0721, 0.3121, 0.2121, 0.0468};// I_NUMB_CENTR = 10;

// Коэффициент модификационного члена
int kr = -1;
	
// Произведение матриц Р*В, используемое в законе управления
float  mPB[24]=     { 0,  0,  0,       0,
                      0,  0, -0.05,    0.1,
                      0,  0, -0.05,    0,
                      0,  0,  0.1417,  0,
                      0,  0,  0.1417, -0.2833,
                      0,  0,  0,       0      };
//float  mPB[24]=     {-0.10,       0,       0,       0,
//                         0, -0.0250, -0.1000, -0.0362,
//                         0, -0.0448, -0.0500,       0,
//                         0,  0.1833,  0.1417,       0,
//                         0,  0.0708,  0.2833,  0.1167,
//                    0.2833,       0,       0,       0};
// Число столбцов матрицы Р*В
//int columns_mPB = 4;

//                theta  psi     gamma    wx     wy   wz
float mK[30] =     {0,  -0.36,   1.9,    0.15,   1,   0,     // servo #1 Aerleron right
                    0,   0.02,   0.73,   0.07,   0,   0.4,   // servo #2 Stabilizer right
                    0,   0.36,  -1.9,   -0.15,  -1,   0,     // servo #3 Aerleron left
                    0,   0,      0,      0,      0,   0,     // servo #4 Rudder
                    0,  -0.02,  -0.73,  -0.07,   0,   0.4};  // servo #5 Stabilizer left

// Вектор весов [19][4], [строк][столбцов]
//float mWeight [172];
//float mWeight [76];
//float mWeight [220];
float mWeight [508];

void processInit( void ) {
}

// Вектор углового положения модели: tetha, psi, gamma, omegax, omegay, omegaz
float vStateVect [6] = {0,0,0,0,0,0};
int secCount=0;
float iDeltaStep [6] = {0.0,0.0,0.0,0.0,0.0,0.0};
int iLab = 0;

float vErrorVect [6];
float vControlVect [4];
float vRBF [I_NUMB_NN];

float mWeightDerive[I_NUMB_W];
float mWeightPrev[I_NUMB_W];

float m1 [4];
float m2[I_NUMB_W];
float m3[I_NUMB_W];
float m4[I_NUMB_W];

void process( void ) {
	//float m5[76];
	float GammaCoef = 100;
	float vPropCntrl [5] = {0,0,0,0,0};
	int i;
	secCount++;

	// Подготовка вектора текущего состояния
	// Вектор углового положения модели: tetha, psi, gamma, omegax, omegay, omegaz
	// Запись текущего вектора положения модели по данным энкодеров
    vStateVect [0] = encoderGet(TETHA).val/57.3; // tetha
	vStateVect [1] = encoderGet(PSI).val/57.3;	// psi
	vStateVect [2] = encoderGet(GAMMA).val/57.3; //gamma

	// Производные углов
    // Запись угловых скоростей из инерциальной системы (после фильтра Калмана)
	vectorData w = imuGyroGet();
    vStateVect [3] = w.x/57.3; // omegax
    vStateVect [4] = w.y/57.3; // omegay
    vStateVect [5] = w.z/57.3; // omegaz

	// Stepwise stabilizer deflection
	if(iLab<9) {
		if (secCount > 3000) {
			iDeltaStep[1] = iDeltaStep[1]-1;
			iDeltaStep[4] = iDeltaStep[4]-1;
			secCount = 0;
			iLab = iLab+1;
		}
	}
	for (i=0;i<I_NUMB_W;i++){
		mWeightPrev[i] = mWeight[i];
	}

	// Вычисление ошибки слежения
	//vErrorVect[0]=0;
	for (i=0;i<3;i++) vErrorVect[i] = vStateVect[i] - vPHIo[i];
	for (i=3;i<6;i++) vErrorVect[i] = vStateVect[i];

	// Вычисление вектора РБФ
	//	fRBF( (float*)vStateVect, (float*)vRBF);
	vRBF[0] = GammaCoef;
	//Набор РБФ для аппроксимации первой переменной вектора состояний *vXin

	for (i=-I_NUMB_CENTR;i<I_NUMB_CENTR+1;i++) {
		vRBF[i+                   (I_NUMB_CENTR+1)] = GammaCoef*expf(-(vStateVect[0]-3*vDelta[0]/I_NUMB_CENTR*i)*(vStateVect[0]-3*vDelta[0]/I_NUMB_CENTR*i)/vSigma[0]);
		vRBF[i+  (2*I_NUMB_CENTR+1)+(I_NUMB_CENTR+1)] = GammaCoef*expf(-(vStateVect[1]-3*vDelta[1]/I_NUMB_CENTR*i)*(vStateVect[1]-3*vDelta[1]/I_NUMB_CENTR*i)/vSigma[1]);
		vRBF[i+2*(2*I_NUMB_CENTR+1)+(I_NUMB_CENTR+1)] = GammaCoef*expf(-(vStateVect[2]-3*vDelta[2]/I_NUMB_CENTR*i)*(vStateVect[2]-3*vDelta[2]/I_NUMB_CENTR*i)/vSigma[2]);
		vRBF[i+3*(2*I_NUMB_CENTR+1)+(I_NUMB_CENTR+1)] = GammaCoef*expf(-(vStateVect[3]-3*vDelta[3]/I_NUMB_CENTR*i)*(vStateVect[3]-3*vDelta[3]/I_NUMB_CENTR*i)/vSigma[3]);
		vRBF[i+4*(2*I_NUMB_CENTR+1)+(I_NUMB_CENTR+1)] = GammaCoef*expf(-(vStateVect[4]-3*vDelta[4]/I_NUMB_CENTR*i)*(vStateVect[4]-3*vDelta[4]/I_NUMB_CENTR*i)/vSigma[4]);
		vRBF[i+5*(2*I_NUMB_CENTR+1)+(I_NUMB_CENTR+1)] = GammaCoef*expf(-(vStateVect[5]-3*vDelta[5]/I_NUMB_CENTR*i)*(vStateVect[5]-3*vDelta[5]/I_NUMB_CENTR*i)/vSigma[5]);
	}

	// -------------------Вычисление закона адаптации весов НС--------------------
	// matr_dw = - sign(d0) * Gamma * vect_RBF * vect_e' * P * B + kr * matr_w;
	//--------------------------------------------------------------------------
	// m1= vect_e' * PB, т.к. применяется транспонирование для vect_e, то строки и столбцы поменялись местами, m1 = 1x4 ( строкХстолбцов)
	matmmltf (vErrorVect, 1, 6, mPB, 4, m1);
	// m2 = Gamma * vect_RBF * m1,  m2 = 127x4
	matmmltf (vRBF, I_NUMB_NN, 1, m1, 4, m2);
	// m3 = kr * matr_w,  m3 = 127x4
	matsmltf (mWeightPrev, kr, I_NUMB_NN, 4, m3);
	// matr_dw = m2+m3
	matmaddf (m2, m3, I_NUMB_NN, 4, mWeightDerive);

	matsmltf (mWeightDerive, dt, I_NUMB_NN, 4, m4);
	matmaddf (mWeightPrev, m4, I_NUMB_NN, 4, mWeight);

	// -------------Вычиление закона управления---------------------
	// ----------/vect_cntrlOut = matr_w'*vect_RBF+vect_propCntrl/-----------------
	// Вычисление произведения
	// matmmltf (p_mWeightTransp, I_NUMB_NN, 4, p_vRBF, 1, p_vControlVect);
	matmmltf (vRBF, 1, I_NUMB_NN, mWeight, 4, vControlVect);

	// vect_propCntrl_tmp = matr_K*vect_e*57.3;
	// vPropCntrl = matr_K*vect_e
	matmmltf (mK, 5, 6, vErrorVect, 1, vPropCntrl);

	// Вычисление углов отклонения органов управления
	servoSet(0,	vDelta_o[0] + *(vControlVect+2)/GammaCoef + *vPropCntrl*57.3);												// Right Dif.Stab
	servoSet(1,	vDelta_o[1] + iDeltaStep[1]+* vControlVect/GammaCoef+*(vControlVect+1)/GammaCoef + *(vPropCntrl+1)*57.3);	// Left  Dif.Stab
	servoSet(2,	vDelta_o[2] - *(vControlVect+2)/GammaCoef + *(vPropCntrl+2)*57.3);           								// Rudder
	servoSet(3,	vDelta_o[3] + *(vControlVect+3)/GammaCoef + *(vPropCntrl+3)*57.3);											// Right Aileron
	servoSet(4,	vDelta_o[4] + iDeltaStep[4]+ * vControlVect/GammaCoef-*(vControlVect+1)/GammaCoef + *(vPropCntrl+4)*57.3);  // Left Aileron
}
