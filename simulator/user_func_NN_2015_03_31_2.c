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

// функции исчисления матриц
  
void Diag_matrix (int rowsize, float filler, float* matrix);

// функция готовит вектор РБФ
void fRBF (const float *vXin, float *vRBF);
// проверка ограничений по сервам
void fServRestr(_DLMOUT *OutData);				

//-----------------------------------------------------------------
//                Глобальные переменные 
//              размещаются в секции .data
//-----------------------------------------------------------------

// Начальные смещения рулей [deg]
float vDelta_o[6]={0,0,0,0,0,0};

// Балансировочные углы - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// Число используемых в законе управления сервоприводов
int N=6; 
                 
// Время дискретизации [сек]
float dt = 0.01;

// Число РБФ
int iNumbNN = 127;

// Ширина шага при определении центров РБФ 
float vDelta [6] = {0.78, 3.14, 0.34, 2, 1, 0.3};

// Ширина шага при определении центров РБФ 
float vSigma [6] = {0.3309, 0.9798, 0.0721, 0.3121, 0.2121, 0.0468};

// Коэффициент модификационного члена
int kr = -14;
	
// Произведение матриц Р*В, используемое в законе управления
float  mPB[24]=     {-0.5000,       0,       0,       0,
				            0,       0, -2.5000, -5.0000,
				            0, -0.5000, -1.2500,       0,
				            0,  1.5833,  3.9583,       0,
				            0,       0,  8.7500, 17.5000,
				       1.4167,       0,       0,       0};
// Число столбцов матрицы Р*В
int columns_mPB = 4;

// Вектор весов [127][4], [строк][столбцов]
float mWeight [508]; 

// Вектор углового положения модели: tetha, psi, gamma, omegax, omegay, omegaz
float vStateVect [6] = {0,0,0,0,0,0};

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
	float vStateVectPrev [3];
	float vErrorVect [6];
	float vControlVect [4];
	float vRBF [iNumbNN];

	float mWeightDerive[508];
	//float mWeightTransp[508];
	float mWeightPrev[508];
	float mGamma[16129];

	float m1 [4];
	float m2[508];
	float m3[508];
	float m4[508];
	float m5[508];
	float Gamma_coef = 10;
	int i;
  	int rows_vErrorVect = 6;	
	
	// Диагональная матрица Гамма, имеющая размер iNumbNN Х iNumbNN, на диагонали расположен элемент Gamma_coef
	Diag_matrix( iNumbNN, Gamma_coef, (float*) mGamma ); 
	
	// Вектор состояния, определённый на предыдущем шаге 
	for (i=0;i<3;i++) {
		vStateVectPrev [i] = vStateVect [i];
	}
  	// Подготовка вектора текущего состояния по данным энкодеров
	// Вектор углового положения модели: tetha, psi, gamma, omegax, omegay, omegaz
	// Запись текущего вектора положения модели по данным энкодеров
	vStateVect [0] = InData->encData[2]; // tetha
	vStateVect [1] = InData->encData[1]; // psi
	vStateVect [2] = InData->encData[0]; // gamma
	// Вычисление угловой скорости по энкодерам
	vStateVect [3] = (vStateVect [2] - vStateVectPrev [2])/dt; // omegax
	vStateVect [4] = (vStateVect [1] - vStateVectPrev [1])/dt; // omegay
	vStateVect [5] = (vStateVect [0] - vStateVectPrev [0])/dt; // omegaz
	if (vStateVectPrev[1]==0){
		vStateVect [3] = 0; // omegax
		vStateVect [4] = 0; // omegay
		vStateVect [5] = 0; // omegaz

	}
	for (i=0;i<508;i++){
		mWeightPrev[i] = mWeight[i];
  	}
	  	
  	// Вычисление ошибки слежения
	for (i=0;i<3;i++) vErrorVect[i] = vStateVect[i] - vPHIo[i];
	for (i=3;i<6;i++) vErrorVect[i] = vStateVect[i];
  	
  	// Вычисление вектора РБФ
	fRBF( (float*)vStateVect, (float*)vRBF);
  	
  	// -------------------Вычисление закона адаптации весов НС-----------------
  	// matr_dw = - sign(d0) * Gamma * vect_RBF * vect_e' * P * B + kr * matr_w;
  	//--------------------------------------------------------------------------
  	// m1= vect_e' * PB, т.к. применяется транспонирование для vect_e, то строки и столбцы поменялись местами, m1 = 1x4 ( строкХстолбцов)
	matmmltf (vErrorVect, 1, rows_vErrorVect, mPB, columns_mPB, m1);
  	// m2 = vect_RBF * m1,  m2 = 127x4 ( строкХстолбцов)
	matmmltf (vRBF, iNumbNN, 1, m1, columns_mPB, m2);
  	// m3 = Gamma * m2,  m3 = 127x4 ( строкХстолбцов) 
	matmmltf (mGamma, iNumbNN, iNumbNN, m2, 4, m3);
  	// m4 = kr * matr_w,  m4 = 127x4 ( строкХстолбцов) 
	matsmltf (mWeightPrev, kr, iNumbNN, 4, m4);
  	// matr_dw = m3+m4 
	matmaddf (m3, m4, iNumbNN, 4, mWeightDerive);
  	
  	// Интегрирование весов НС метдом Эйлера
	matsmltf (mWeightDerive, dt, iNumbNN, 4, m5);
	matmaddf (mWeightPrev, m5, iNumbNN, 4, mWeight);
  	
  	// -------------Вычиление закона управления---------------------
  	// ----------/vect_cntrlOut = matr_w'*vect_RBF/-----------------
  	// Транспонирование матрицы весов  
  	// transpmf (p_mWeight, iNumbNN, 4, p_mWeightTransp);
  	// Вычисление произведения 	
  	// matmmltf (p_mWeightTransp, iNumbNN, 4, p_vRBF, 1, p_vControlVect);
	matmmltf (vRBF, 1, iNumbNN, mWeight, 4, vControlVect);
  	// Вычмление углов отклонения органов управления
	OutData->ANGL[0] = vDelta_o[0] + *(vControlVect+2); // элерон правый
	OutData->ANGL[1] = vDelta_o[1] + * vControlVect+*(vControlVect+1); // ГО правое
	OutData->ANGL[2] = vDelta_o[2] - *(vControlVect+2); // элерон левый
	OutData->ANGL[3] = vDelta_o[3] + *(vControlVect+3); // Руль направлений
	OutData->ANGL[4] = vDelta_o[4] + * vControlVect-*(vControlVect+1); // ГО левое
  	
  	// Нужно добавить проверку ограничений по сервам
	fServRestr(OutData);
  						    
	return 0;  // NO_ERROR -> servos activated!
}

//---------------------------------------------------------------
//                  Подпрограммы функции DLM
//       Внутренние переменные размещаются в секции .bss
//         Коды подпрограмм размещаются в секции .text
//---------------------------------------------------------------
//
// Проверка, чтобы расчетные значения для отклонения органов не выходили за ограничения
void fServRestr (_DLMOUT *OutData){
//servo#1
    if      ( OutData->ANGL[0] < -22)
        OutData->ANGL[0] = -22; 
    else if ( OutData->ANGL[0] >  22)
        OutData->ANGL[0] =  22; 
//servo#2
    if      ( OutData->ANGL[1] < -32)
        OutData->ANGL[1] = -32; 
    else if ( OutData->ANGL[1] >  32)
        OutData->ANGL[1] =  32; 
//servo#3
    if      ( OutData->ANGL[2] < -22)
        OutData->ANGL[2] = -22; 
    else if ( OutData->ANGL[2] >  22)
        OutData->ANGL[2] =  22; 
//servo#4
    if      ( OutData->ANGL[3] < -22)
        OutData->ANGL[3] = -22; 
    else if ( OutData->ANGL[3] >  22)
        OutData->ANGL[3] =  22; 
//servo#5
    if      ( OutData->ANGL[4] < -32)
        OutData->ANGL[4] = -32; 
    else if ( OutData->ANGL[4] >  32)
        OutData->ANGL[4] =  32;      
}

void fRBF (const float *vStateVect, float *vRBF){
	int i;
	*vRBF = 1;
	//Набор РБФ для аппроксимации первой переменной вектора состояний *vXin
	for (i=-10;i<11;i++){
		vRBF[i+11] = expf(-(vStateVect[0]-vDelta[0]*i)*(vStateVect[0]-vDelta[0]*i)/vSigma[0]);
		vRBF[i+32] = expf(-(vStateVect[1]-vDelta[1]*i)*(vStateVect[1]-vDelta[1]*i)/vSigma[1]);
		vRBF[i+53] = expf(-(vStateVect[2]-vDelta[2]*i)*(vStateVect[2]-vDelta[2]*i)/vSigma[2]);
		vRBF[i+74] = expf(-(vStateVect[3]-vDelta[3]*i)*(vStateVect[3]-vDelta[3]*i)/vSigma[3]);
		vRBF[i+95] = expf(-(vStateVect[4]-vDelta[4]*i)*(vStateVect[4]-vDelta[4]*i)/vSigma[4]);
		vRBF[i+116]= expf(-(vStateVect[5]-vDelta[5]*i)*(vStateVect[5]-vDelta[5]*i)/vSigma[5]);
	}
}
void Diag_matrix (int rowsize, float filler, float* matrix){
	
	int i, j;
	
    	for (i=0;i<rowsize;i++){
    		
    		for(j=0;j<rowsize;j++){
       			if (i==j){
					*matrix = filler;
					matrix++;
       			}
       			else{
					*matrix = 0;
					matrix++;
       			}
    		}
   		}
//   return (int*) matrix;
}
