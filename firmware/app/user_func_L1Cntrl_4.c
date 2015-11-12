#include <math.h>
#include <matrix.h>
#include <stdlib.h>
#include <stdio.h>
#include "servo.h"
#include "encoder.h"

// Начальные смещения рулей [deg]
float vDelta_o[5]={0,-12,0,0,-12};

// Балансировочные углы - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// Время дискретизации [сек]
float dt = 0.02;

// Число используемых в законе управления сервоприводов
int N=6; 
int secCount=0;

// Вектор углового положения модели
float vStateVect [6] = {0,0,0,0,0,0};

float iDeltaStep [6] = {0.0,-1.0,0.0,0.0,-1.0,0.0};

float vUk[4]  = {0, 0, 0, 0};
float vXek[4] = {0, 0, 0, 0};
float vLatVar [4]; // Vector of lateral variables gamma, psi, wx, wy

void processInit( void ) {
	//print("first\n\r");
	vXek[0] = encoderGet(GAMMA).val;		//gamma
	vXek[1] = encoderGet(PSI).val;			//psi
	vXek[2] = imuGyroGet().x;				//wx
	vXek[3] = imuGyroGet().y;				//wy
	vLatVar[0] = encoderGet(GAMMA).val;		//gamma
	vLatVar[1] = encoderGet(PSI).val;		//psi
	vLatVar[2] = imuGyroGet().x;			//wx
	vLatVar[3] = imuGyroGet().y;			//wy
	int secCount=0;
}


void process( void ) {
	float vLatError[4], m1[4], m2[4], m3[4], m4[4], m5[4], vUkNew[4], vXekNew[4];
    float fUStab;
    int i;
    float fUa = 0;
    float vULat [2];
	vULat[0]=0;
	vULat[1]=0;
	//print("user\n\r");
	// Control matrices
	float a12[16]={1.0000,         0,         0,   -0.0295,
				   0.0200,    1.0000,         0,   -0.0479,
						0,    0.0800,    1.0000,   -0.1097,
						0,         0,    0.1600,    0.7867};

	float a13[16]={3.7459,         0,         0,         0,
				   4.0981,         0,         0,         0,
				   6.3285,         0,         0,         0,
				   3.6311,         0,         0,         0};

	float a21[16]={1.0000,         0,    0.0200,    0.0426,
				   0,         1.0000,         0,   -0.0471,
				  -2.3418,    0.0468,    0.7448,   -0.4020,
				  -0.1116,    0.0251,   -0.0178,    0.8927};

	float a22[16]={      0,         0,         0,         0,
						 0,         0,         0,         0,
						 0,         0,         0,    0.1600,
						 0,         0,         0,         0};

	float a23[16]={-1.8155,       0,         0,         0,
					1.2526,       0,         0,         0,
				   -2.1940,       0,         0,         0,
					3.5619,       0,         0,         0};


	float cAdapt = -0.1536;
	float mKLat[2][4] = {{ 0.8546,   -0.0314,    0.1140,    0.1847},
						 {-2.6145,    1,   -0.2351,   -1.2326}};
	float fKln = 0.4;

    secCount++;
    //tetha, psi, gamma, omegax, omegay, omegaz
    vStateVect [0] = encoderGet(TETHA).val; // tetha
	vStateVect [1] = encoderGet(PSI).val;	// psi
	vStateVect [2] = encoderGet(GAMMA).val; //gamma
	//print("user %f %f %f\n\r", vStateVect[0], vStateVect[1], vStateVect[2]);
	vStateVect [3] = imuGyroGet().x; // omegax
	vStateVect [4] = imuGyroGet().y; // omegay
	vStateVect [5] = imuGyroGet().z; // omegaz
    // Stepwise stabilizer deflection
    if (secCount > 3000) {
        iDeltaStep[1] = iDeltaStep[1]-1;
        iDeltaStep[4] = iDeltaStep[4]-1;
        secCount = 0;
    }
    // Vector of lateral variables
    vLatVar[0] = vStateVect [2];//gamma
    vLatVar[1] = vStateVect [1];//psi
    vLatVar[2] = vStateVect [3];//wx
    vLatVar[3] = vStateVect [4];//wy
    for (i=0;i<4;i++) vLatError[i]=vXek[i]-vLatVar[i];
    // L1 adaptive control
    // uk1  = a12*uk+a13*(xek-xk);
    // m1 = a12*uk
    /*matmmltf (a12, 4, 4, vUk, 1, m1);
    // m2 = a13*(xek-xk)
    matmmltf (a13, 4, 4, vLatError, 1, m2);
    //for (i=0;i<4;i++) vUkNew[i] = m1[i]+m2[i];
    // xekNew = a21*xek+a22*uk+a23*(xek-xk)
    // m3 = a21*xek
    matmmltf (a21, 4, 4, vXek, 1, m3);
    // m4 = a22*vUk
    matmmltf (a22, 4, 4, vUk, 1, m4);
    // m5 = a23*(xek-xk)
    matmmltf (a23, 4, 4, vLatError, 1, m5);
    for (i=0;i<4;i++) {
        vUkNew[i]  = m1[i] + m2[i];
        vXekNew[i] = m3[i] + m4[i] + m5[i];
    }
    // Adaptive control ua=ca*uk
    fUa = cAdapt*vUk[3];
    // Lateral control
    for (i=0;i<4;i++) {
        vULat[0] = vULat[0]+mKLat[0][i]*vLatVar[i];
        vULat[1] = vULat[1]+mKLat[1][i]*vLatVar[i];
    }
    //Control calculations: Stabilizer, Differential stabilizer, Rudder[deg]
    fUStab  = fKln*vStateVect [5]; // fUStab = Kln*wz
	servoSet(1,	vDelta_o[1]+iDeltaStep[1]+fUStab +  vULat[0]);	// Right Dif.Stab
	servoSet(4,	vDelta_o[4]+iDeltaStep[4]+fUStab -  vULat[0]);	// Left  Dif.Stab
	servoSet(3,	-vDelta_o[3]-vULat[1]);           				// Rudder
	servoSet(0,	vDelta_o[0]+fUa);								// Right Aileron
	servoSet(2,	vDelta_o[2]-fUa);    							// Left Aileron
    for (i=0;i<4;i++){
        vXek[i] = vXekNew[i];
        vUk [i] = vUkNew [i];
    } */
//    fServRestr(OutData);
}
//void fServRestr (_DLMOUT *OutData){
//servo#1
//    if      ( OutData->ANGL[0] < -22)
//        OutData->ANGL[0] = -22;
//    else if ( OutData->ANGL[0] >  22)
//        OutData->ANGL[0] =  22;
//servo#2
//    if      ( OutData->ANGL[1] < -32)
//        OutData->ANGL[1] = -32;
//    else if ( OutData->ANGL[1] >  32)
//        OutData->ANGL[1] =  32;
//servo#3
//    if      ( OutData->ANGL[2] < -22)
//        OutData->ANGL[2] = -22;
//    else if ( OutData->ANGL[2] >  22)
//        OutData->ANGL[2] =  22;
//servo#4
//    if      ( OutData->ANGL[3] < -22)
//        OutData->ANGL[3] = -22;
//    else if ( OutData->ANGL[3] >  22)
//        OutData->ANGL[3] =  22;
//servo#5
//    if      ( OutData->ANGL[4] < -32)
//        OutData->ANGL[4] = -32;
//    else if ( OutData->ANGL[4] >  32)
//        OutData->ANGL[4] =  32;
//}
