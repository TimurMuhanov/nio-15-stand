/*---------------------------------------------------------------*/
/*                                                               */
/*  � � � � � � � � � � �   � � � � � � � � � � �   � � � � � �  */
/*                      (��� ������ DLM)                         */
/*                 ���������� ������� ������:                    */
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
//      ��������� ������ ��� ���������� ����� � ������� DLM
//-----------------------------------------------------------------
typedef struct { 		         // input data struct
     float W[3];        // wx, wy, wz �� ������� ������� [deg/s]
     float Wk[3];       // wx, wy, wz ����� ������� ������� [deg/s]
     float PHI[3];      // gamma, teta, psi �� ������� ������� [deg]
     float encData[3];  // ������ - encoder1,2,3 [deg]
} _DLMIN;

typedef struct { 		         // out data struct
     float ANGL[6];	     // ���� ���������� ������� ���������� � [deg]
} _DLMOUT;

//-----------------------------------------------------------------
//                ��������� ������� DLM
//-----------------------------------------------------------------
int main(const _DLMIN *InData, _DLMOUT *OutData);

// ������� ���������� ������
  
void Diag_matrix (int rowsize, float filler, float* matrix);

// ������� ������� ������ ���
void fRBF (const float *vXin, float *vRBF);
// �������� ����������� �� ������
void fServRestr(_DLMOUT *OutData);				

//-----------------------------------------------------------------
//                ���������� ���������� 
//              ����������� � ������ .data
//-----------------------------------------------------------------

// ��������� �������� ����� [deg]
float vDelta_o[6]={0,0,0,0,0,0};

// ��������������� ���� - teta, gamma, psi [deg]
float vPHIo[3]={0,0,0};

// ����� ������������ � ������ ���������� �������������
int N=6; 
                 
// ����� ������������� [���]
float dt = 0.01;

// ����� ���
int iNumbNN = 127;

// ������ ���� ��� ����������� ������� ��� 
float vDelta [6] = {0.78, 3.14, 0.34, 2, 1, 0.3};

// ������ ���� ��� ����������� ������� ��� 
float vSigma [6] = {0.3309, 0.9798, 0.0721, 0.3121, 0.2121, 0.0468};

// ����������� ���������������� �����
int kr = -14;
	
// ������������ ������ �*�, ������������ � ������ ����������
float  mPB[24]=     {-0.5000,       0,       0,       0,
				            0,       0, -2.5000, -5.0000,
				            0, -0.5000, -1.2500,       0,
				            0,  1.5833,  3.9583,       0,
				            0,       0,  8.7500, 17.5000,
				       1.4167,       0,       0,       0};
// ����� �������� ������� �*�
int columns_mPB = 4;

// ������ ����� [127][4], [�����][��������]
float mWeight [508]; 

// ������ �������� ��������� ������
float vStateVect [6] = {0,0,0,0,0,0};

//-----------------------------------------------------------------
//           ���������� ���������� �� ������� DLM
//   ������� ������������ ���� ���������� ������������� ��������
//   ���������� ��������� �� ��������� ������ � ��������� _DLMIN.
//   ������������ ���� � �������� ���������� � ��������� _DLMOUT.
//
//   ���� ������� ���������� ������� ��������, �� ����� �����������
//   �� ����������� ����, ���� ���, �� ����� ��������������� � 0.
//
//   ����� ���������� ��������������� ���� ~4000 ������ ��� 10 ���
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
	
	// ������������ ������� �����, ������� ������ iNumbNN � iNumbNN, �� ��������� ���������� ������� Gamma_coef
	Diag_matrix( iNumbNN, Gamma_coef, (float*) mGamma );
  	  	  	
  	// ���������� �������� ������� �� ������ ���������
	for (i=0;i<3;i++) {
		vStateVectPrev [i] = vStateVect [i];
	  	// ������ �������� ������� ��������� ������ �� ������ ���������
		vStateVect [i] = InData->encData[i];
		// ���������� ������� �������� �� ���������
		vStateVect [3+i] = (vStateVect [i] - vStateVectPrev [i])/dt;
  	}  	
  	
	for (i=0;i<508;i++){
		mWeightPrev[i] = mWeight[i];
  	}
	  	
  	// ���������� ������ ��������
	for (i=0;i<3;i++) vErrorVect[i] = vStateVect[i] - vPHIo[i];
	for (i=3;i<6;i++) vErrorVect[i] = vStateVect[i];
  	
  	// ���������� ������� ���
	fRBF( (float*)vStateVect, (float*)vRBF);
  	
  	// -------------------���������� ������ ��������� ����� ��-----------------
  	// matr_dw = - sign(d0) * Gamma * vect_RBF * vect_e' * P * B + kr * matr_w;
  	//--------------------------------------------------------------------------
  	// m1= vect_e' * PB, �.�. ����������� ���������������� ��� vect_e, �� ������ � ������� ���������� �������, m1 = 1x4 ( ��������������)
	matmmltf (vErrorVect, 1, rows_vErrorVect, mPB, columns_mPB, m1);
  	// m2 = vect_RBF * m1,  m2 = 127x4 ( ��������������)
	matmmltf (vRBF, iNumbNN, 1, m1, columns_mPB, m2);
  	// m3 = Gamma * m2,  m3 = 127x4 ( ��������������) 
	matmmltf (mGamma, iNumbNN, iNumbNN, m2, 4, m3);
  	// m4 = kr * matr_w,  m4 = 127x4 ( ��������������) 
	matsmltf (mWeightPrev, kr, iNumbNN, 4, m4);
  	// matr_dw = m3+m4 
	matmaddf (m3, m4, iNumbNN, 4, mWeightDerive);
  	
  	// �������������� ����� �� ������ ������
	matsmltf (mWeightDerive, dt, iNumbNN, 4, m5);
	matmaddf (mWeightPrev, m5, iNumbNN, 4, mWeight);
  	
  	// -------------��������� ������ ����������---------------------
  	// ----------/vect_cntrlOut = matr_w'*vect_RBF/-----------------
  	// ���������������� ������� �����  
  	// transpmf (p_mWeight, iNumbNN, 4, p_mWeightTransp);
  	// ���������� ������������ 	
  	// matmmltf (p_mWeightTransp, iNumbNN, 4, p_vRBF, 1, p_vControlVect);
	matmmltf (vRBF, 1, iNumbNN, mWeight, 4, vControlVect);
  	// ��������� ����� ���������� ������� ����������
	OutData->ANGL[0] = vDelta_o[0] + *(vControlVect+2); // ������ ������
	OutData->ANGL[1] = vDelta_o[1] + * vControlVect+*(vControlVect+1); // �� ������
	OutData->ANGL[2] = vDelta_o[2] - *(vControlVect+2); // ������ �����
	OutData->ANGL[3] = vDelta_o[3] + *(vControlVect+3); // ���� �����������
	OutData->ANGL[4] = vDelta_o[4] + * vControlVect-*(vControlVect+1); // �� �����
  	
  	// ����� �������� �������� ����������� �� ������
	fServRestr(OutData);
  						    
	return 0;  // NO_ERROR -> servos activated!
}

//---------------------------------------------------------------
//                  ������������ ������� DLM
//       ���������� ���������� ����������� � ������ .bss
//         ���� ����������� ����������� � ������ .text
//---------------------------------------------------------------
//
// ��������, ����� ��������� �������� ��� ���������� ������� �� �������� �� �����������
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
	vRBF[0] = 1;
	//����� ��� ��� ������������� ������ ���������� ������� ��������� *vXin
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
