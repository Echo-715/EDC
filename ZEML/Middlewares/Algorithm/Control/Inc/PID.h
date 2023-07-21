#ifndef __PID_H_
#define __PID_H_
#include "main.h"
#include "math_common.h"

typedef float PIDElem_t;				//PIDԪ������
#define Constrain_PID(amt,high,low)		constrain(amt,high,low) //PID�޷�
typedef struct {
	PIDElem_t KP;						//��������
	PIDElem_t KI;						//��������
	PIDElem_t KD;						//΢������
	PIDElem_t PMax;						//�������ֵ
	PIDElem_t IMax;						//�������ֵ
	PIDElem_t DMax;						//΢�����ֵ
	PIDElem_t PIDMax;					//PID���ֵ
	PIDElem_t PIDMin;					//PID���ֵ
	PIDElem_t IntegralValue;			//����
	PIDElem_t DiffValue;				//���
	PIDElem_t MissValue;				//���仯��
	PIDElem_t AngleMax;					//�Ƕ����ֵ
} PIDConfig_t;

typedef enum 
{
	PID_P_Constrain = 0,
	PID_I_Constrain,
	PID_D_Constrain,
	PID_PID_Constrain
} PID_Constrain_Config_t;

void PID_Init(PIDConfig_t *PID_Config,PIDElem_t K_P,PIDElem_t K_I,PIDElem_t K_D,PIDElem_t P_Max,PIDElem_t I_Max,PIDElem_t D_Max,PIDElem_t PID_Max,PIDElem_t PID_Min);
void PID_Zero_Processing_Init(PIDConfig_t *PID_Config,PIDElem_t AngleMax);

PIDElem_t Basic_PID_Controller(PIDConfig_t* PIDConfig,PIDElem_t E_value, PIDElem_t C_value);
PIDElem_t Basic_PI_Controller(PIDConfig_t* PIDConfig,PIDElem_t E_value, PIDElem_t C_value);
PIDElem_t Zero_Processing_PID_Controller(PIDConfig_t* PIDConfig,PIDElem_t E_value, PIDElem_t C_value);

void PID_Constrain_Config(PIDConfig_t* PIDConfig,PID_Constrain_Config_t PID_Constrain,PIDElem_t new_max,PIDElem_t new_min);
void PID_Integral_Config(PIDConfig_t *PID_Config,PIDElem_t integral_value);
void PID_Config(PIDConfig_t *PID_Config,PIDElem_t K_P,PIDElem_t K_I,PIDElem_t K_D,PIDElem_t P_Max,PIDElem_t I_Max,PIDElem_t D_Max);
void PID_Reset(PIDConfig_t* PIDConfig);
#endif
