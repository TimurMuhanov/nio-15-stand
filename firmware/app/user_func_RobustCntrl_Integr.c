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


//-----------------------------------------------------------------
//                Глобальные переменные 
//              размещаются в секции .data
//-----------------------------------------------------------------

// Начальные смещения рулей [deg]
float vDelta_o[5]={0,-12,0,0,-12};

// Балансировочные углы - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// Время дискретизации [сек]
float dt = 0.02;
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
float Kij[6][6]={{0,  2.33, -0.58,  0.22, 0.91,   0},   // servo #1 Aerleron right
                 {0,  0.27,0.07,  0.04, 0.00, 0.4},   // servo #2 Stabilizer right
                 {0, -2.33,0.58, -0.22,-0.91,   0},   // servo #3 Aerleron left
                 {0, 0.84,-0.54, 0.05,0.63,   0},   // servo #4 Rudder
                 {0, -0.27,-0.07, -0.04,  0.0, 0.4},   // servo #5 Stabilizer left
                 {0,     0,    0,     0,    0,   0}};  // servo #6 
float fKint = -0.1;
// Число используемых в законе управления сервоприводов
int N=5; 
int secCount=0;

// Вектор углового положения модели
float vStateVect [6] = {0,0,0,0,0,0};
float iDeltaStep [6] = {0.0,0.0,0.0,0.0,0.0,0.0};

// Внутренняя переменная
float fIntVar = 0;
//Счётчик отклонений стабилизатора
int iLab = 0;

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
    float fUint;
    int i;

    secCount++;
    // Подготовка вектора текущего состояния
    // Вектор углового положения модели: tetha, psi, gamma, omegax, omegay, omegaz
    // Запись текущего вектора положения модели по данным энкодеров
    vStateVect [0] = InData->encData[2]; // tetha
    vStateVect [1] = InData->encData[1]; // psi
    vStateVect [2] = InData->encData[0]; // gamma
    // Запись угловых скоростей из инерциальной системы (после фильтра Калмана)
    vStateVect [3]=InData->Wk[0]; // omegax
    vStateVect [4]=InData->Wk[1]; // omegay
    vStateVect [5]=InData->Wk[2]; // omegaz
    // Stepwise stabilizer deflection
//    if(iLab<13) {
//    if (secCount > 3000) {
//        iDeltaStep[1] = iDeltaStep[1]-1;
//        iDeltaStep[4] = iDeltaStep[4]-1;
//        secCount = 0;
//        iLab = iLab+1;
//    }
//    }
    // Интеграл
    fUint   = fKint*fIntVar;
    fIntVar = dt*vStateVect [1]+fIntVar;

    for (i=0;i<N;i++){
          OutData->ANGL[i] = vDelta_o[i] +
                             Kij[i][0]*(vStateVect [0] - vPHIo[0]) + //teta
                             Kij[i][1]*(vStateVect [2] - vPHIo[1]) +  //gamma
                             Kij[i][2]*(vStateVect [1] - vPHIo[2]) +  //psi
                             Kij[i][3]*vStateVect [3] +               //wx
                             Kij[i][4]*vStateVect [4] +               //wy
                             Kij[i][5]*vStateVect [5] + iDeltaStep[i];                //wz
    }
    OutData->ANGL[0]=OutData->ANGL[0]+fUint;    // Right Aileron
    OutData->ANGL[2]=OutData->ANGL[2]-fUint;    // Right Aileron
      return 0;  // NO_ERROR -> servos activated!
}

//---------------------------------------------------------------
//                  Подпрограммы функции DLM
//       Внутренние переменные размещаются в секции .bss
//         Коды подпрограмм размещаются в секции .text
//---------------------------------------------------------------
//
// Проверка, чтобы расчетные значения для отклонения органов не выходили за ограничения
