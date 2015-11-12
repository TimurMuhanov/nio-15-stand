/*---------------------------------------------------------------*/
/*                                                               */
/*  Д И Н А М И Ч Е С К И   З А Г Р У Ж А Е М Ы Й   М О Д У Л Ь  */
/*                      (Это шаблон DLM)                         */
/*                 Предельные размеры секций:                    */
/*                        .text - 16 kB                          */
/*                        .data - 4 kB                           */
/*                        .bss  - 4 kB                           */
/*                                                               */
/*---------------------------------------------------------------*/
#include <math.h>
#include <matrix.h>
#include <stdlib.h>
#include <stdio.h>

//-----------------------------------------------------------------
//      Структуры данных для управления серво с помощью DLM
//-----------------------------------------------------------------
typedef struct { 		         // input data struct
     float W[3];        // wx, wy, wz до фильтра Калмана [deg/s]
     float Wk[3];       // wx, wy, wz после фильтра Калмана [deg/s]
     float PHI[3];      // gamma, teta, psi от фильтра Калмана [deg]
     float encData[3];  // данные - encoder1,2,3 [deg]
} _DLMIN;

typedef struct { 		         // out data struct
     float ANGL[6];	     // углы отклонения органов управления в [deg]
} _DLMOUT;

//-----------------------------------------------------------------
//                Прототипы функций DLM
//-----------------------------------------------------------------
int main(const _DLMIN *InData, _DLMOUT *OutData);

//void fServRestr(_DLMOUT *OutData);

//-----------------------------------------------------------------
//                Глобальные переменные 
//              размещаются в секции .data
//-----------------------------------------------------------------

// Начальные смещения рулей [deg]
float vDelta_o[5]={0,0,0,0,0};

// Балансировочные углы - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// Время дискретизации [сек]
float dt = 0.02;

// Число используемых в законе управления сервоприводов
int N=6; 
int secCount=0;
int isFirst = 0;

// Вектор углового положения модели
float vStateVect [6] = {0,0,0,0,0,0};

float iDeltaStep [6] = {0.0,-1.0,0.0,0.0,-1.0,0.0};

float vUk[4]  = {0, 0, 0, 0};
float vXek[4] = {0, 0, 0, 0};
//-----------------------------------------------------------------
//           Вызываемая встроенным ПО функция DLM
//   Функция рассчитывает углы отклонения сервоприводов согласно
//   некоторому алгоритму на основании данных в структуре _DLMIN.
//   Рассчитанные углы в градусах передаются в структуру _DLMOUT.
//
//   Если функция возвращает нулевое значение, то серво отклоняются
//   на расчитанные углы, если нет, то серво устанавливаются в 0.
//
//   Время выполнения представленного кода ~4000 циклов или 10 мкс
//-----------------------------------------------------------------

int umain(const _DLMIN *InData, _DLMOUT *OutData)
{
    float vLatError[4], m1[4], m2[4], m3[4], m4[4], m5[4], vUkNew[4], vXekNew[4];
    float vLatVar [4]; // Vector of lateral variables gamma, psi, wx, wy
    float fUStab;
    int i;
    float fUa = 0;
    float vULat [2];
	vULat[0]=0;
	vULat[1]=0;
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
                     {-2.6145,    0.3649,   -0.2351,   -1.2326}};
float fKln = 0.4;

    if(isFirst==0) {
        vXek[0] = InData->encData[0];//gamma
        vXek[1] = InData->encData[1];//psi
        vXek[2] = InData->Wk[0];//wx
        vXek[3] = InData->Wk[1];//wy
        vLatVar[0] = InData->encData[0];//gamma
        vLatVar[1] = InData->encData[1];//psi
        vLatVar[2] = InData->Wk[0];//wx
        vLatVar[3] = InData->Wk[1];//wy
        isFirst = 1;
    }

    secCount++;
    //tetha, psi, gamma, omegax, omegay, omegaz
    vStateVect [0] = InData->encData[2]; // tetha
    vStateVect [1] = InData->encData[1]; // psi
    vStateVect [2] = InData->encData[0]; // gamma
    vStateVect [3] = InData->Wk[0]; // omegax
    vStateVect [4] = InData->Wk[1]; // omegay
    vStateVect [5] = InData->Wk[2]; // omegaz
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
    matmmltf (a12, 4, 4, vUk, 1, m1);
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
    OutData->ANGL[1] = vDelta_o[1]+iDeltaStep[1]+fUStab +  vULat[0]; // Right Dif.Stab
    OutData->ANGL[4] = vDelta_o[4]+iDeltaStep[4]+fUStab -  vULat[0]; // Left  Dif.Stab
    OutData->ANGL[3] = vDelta_o[3]+vULat[1];           // Rudder
    OutData->ANGL[0] = vDelta_o[0]+fUa;    // Right Aileron
    OutData->ANGL[2] = vDelta_o[2]-fUa;    // Left Aileron
    for (i=0;i<4;i++){
        vXek[i] = vXekNew[i];
        vUk [i] = vUkNew [i];
    }
//    fServRestr(OutData);
    return 0;  // NO_ERROR -> servos activated!
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
//---------------------------------------------------------------
//                  Подпрограммы функции DLM
//       Внутренние переменные размещаются в секции .bss
//         Коды подпрограмм размещаются в секции .text
//---------------------------------------------------------------
//
// Проверка, чтобы расчетные значения для отклонения органов не выходили за ограничения
