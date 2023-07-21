#include "PID.h"

#ifndef Mul
#define TEMP_MUL
#define Mul(a,b) ((a)*(b))
#endif


/// @brief PID��ʼ��
/// @param PID_Config PID���ýṹ��
/// @param K_P ��������
/// @param K_I ��������
/// @param K_D ΢������
/// @param P_Max �������ֵ
/// @param I_Max �������ֵ
/// @param D_Max ΢�����ֵ
/// @param PID_Max PID���ֵ
/// @param PID_Min PID��Сֵ
void PID_Init(PIDConfig_t *PID_Config,PIDElem_t K_P,PIDElem_t K_I,PIDElem_t K_D,PIDElem_t P_Max,PIDElem_t I_Max,PIDElem_t D_Max,PIDElem_t PID_Max,PIDElem_t PID_Min)
{
	PID_Config->KP = K_P;						//��������
	PID_Config->KI = K_I;						//��������
	PID_Config->KD = K_D;						//΢������
	PID_Config->PMax = P_Max;					//�������ֵ
    PID_Config->IMax = I_Max;					//�������ֵ
	PID_Config->DMax = D_Max;					//΢�����ֵ
	PID_Config->PIDMax = PID_Max;				//PID���ֵ
	PID_Config->PIDMin = PID_Min;				//PID���ֵ
	PID_Config->IntegralValue = 0;				//����
	PID_Config->DiffValue = 0;					//���
}
/// @brief ����PID����ֵ
/// @param PID_Config PID���ýṹ��
/// @param integral_value ����ֵ
void PID_Integral_Config(PIDConfig_t *PID_Config,PIDElem_t integral_value)
{
	PID_Config->IntegralValue = integral_value;
}
/// @brief ����PID����
/// @param PID_Config PID���ýṹ��
/// @param K_P ��������
/// @param K_I ��������
/// @param K_D ΢������
/// @param P_Max �������ֵ
/// @param I_Max �������ֵ
/// @param D_Max ΢�����ֵ
void PID_Config(PIDConfig_t *PID_Config,PIDElem_t K_P,PIDElem_t K_I,PIDElem_t K_D,PIDElem_t P_Max,PIDElem_t I_Max,PIDElem_t D_Max)
{
	PID_Config->KP = K_P;						//��������
	PID_Config->KI = K_I;						//��������
	PID_Config->KD = K_D;						//΢������
	PID_Config->PMax = P_Max;					//�������ֵ
    PID_Config->IMax = I_Max;					//�������ֵ
	PID_Config->DMax = D_Max;					//΢�����ֵ
}
/// @brief PID����㴦���ʼ��
/// @param PID_Config PID���ýṹ��
/// @param AngleMax �Ƕ����ֵ[-AngleMax,,AngleMax]
void PID_Zero_Processing_Init(PIDConfig_t *PID_Config,PIDElem_t AngleMax)
{
	PID_Config->AngleMax = AngleMax;          //�Ƕ�����
}

/// @brief ����λ��ʽPID������
/// @param PIDConfig PID���ýṹ��
/// @param E_value ����ֵ
/// @param C_value ��ǰֵ
/// @return ��ǰPID���
__attribute__((section("ccmram"))) PIDElem_t Basic_PID_Controller(PIDConfig_t* PIDConfig,PIDElem_t E_value, PIDElem_t C_value)
{
	PIDElem_t CurrentValue = 0;
	PIDElem_t new_DiffValue = 0;
	//��ǰ���
	new_DiffValue = Constrain_PID(E_value - C_value,PIDConfig->PMax,-PIDConfig->PMax);
	
	//��������(�����ĵ���)
	PIDConfig->MissValue = Constrain_PID(new_DiffValue - PIDConfig->DiffValue,PIDConfig->DMax,-PIDConfig->DMax);
	PIDConfig->DiffValue = new_DiffValue;

	//�������
	PIDConfig->IntegralValue += PIDConfig->DiffValue;
	
	//�����ֱ���
	PIDConfig->IntegralValue = Constrain_PID(PIDConfig->IntegralValue,PIDConfig->IMax,-PIDConfig->IMax);

	//PID
	CurrentValue = Mul(PIDConfig->KP,PIDConfig->DiffValue) + Mul(PIDConfig->KI,PIDConfig->IntegralValue) + Mul(PIDConfig->KD,PIDConfig->MissValue);

	//��PID����
	return Constrain_PID(CurrentValue,PIDConfig->PIDMax,PIDConfig->PIDMin);
}

/// @brief ����λ��ʽPI������
/// @param PIDConfig PI���ýṹ��
/// @param E_value ����ֵ
/// @param C_value ��ǰֵ
/// @return ��ǰPID���
__attribute__((section("ccmram"))) PIDElem_t Basic_PI_Controller(PIDConfig_t* PIDConfig,PIDElem_t E_value, PIDElem_t C_value)
{
	PIDElem_t CurrentValue = 0;
	PIDElem_t new_DiffValue = 0;
	//���KD�Ƿ�Ϊ0����ֹʹ��PID������ʱ�������PI������
	assert_param((PIDConfig->KD == 0));
	//��ǰ���
	PIDConfig->DiffValue = Constrain_PID(E_value - C_value,PIDConfig->PMax,-PIDConfig->PMax);
	
	//�������
	PIDConfig->IntegralValue += PIDConfig->DiffValue;
	
	//�����ֱ���
	PIDConfig->IntegralValue = Constrain_PID(PIDConfig->IntegralValue,PIDConfig->IMax,-PIDConfig->IMax);

	//PID
	CurrentValue = Mul(PIDConfig->KP,PIDConfig->DiffValue) + Mul(PIDConfig->KI,PIDConfig->IntegralValue);

	//��PID����
	return Constrain_PID(CurrentValue,PIDConfig->PIDMax,PIDConfig->PIDMin);
}


/// @brief ����㴦���PID������
/// @param PIDConfig PID���ýṹ��
/// @param E_value ����ֵ
/// @param C_value ��ǰֵ
/// @return ��ǰPID���
/// @attention ��㴦���Ƿ�ΧΪ[0,AngleMax],����Χ��[-AngleMax,AngleMax]��Ҫ����AngleMax/2
__attribute__((section("ccmram"))) PIDElem_t Zero_Processing_PID_Controller(PIDConfig_t* PIDConfig,PIDElem_t E_value, PIDElem_t C_value)
{
	//�Ƕ�ͻ��㴦��
	//��е�Ƕȳ�����������Ҫ����������ڣ���ʱҪ����ͻ���
	if (abs(C_value - E_value) > (PIDConfig->AngleMax/2))
	{
		E_value += (E_value > C_value) ? -PIDConfig->AngleMax : PIDConfig->AngleMax;
	}
	return Basic_PID_Controller(PIDConfig,E_value, C_value);
}
__attribute__((section("ccmram"))) /// @brief ����PID�ڲ�����
/// @param PIDConfig PID����
void PID_Reset(PIDConfig_t* PIDConfig)
{
	PIDConfig->DiffValue = 0;
	PIDConfig->IntegralValue = 0;
	PIDConfig->MissValue = 0;
}
/// @brief PID�޷�����
/// @param PIDConfig PID���ýṹ��
/// @param PID_Constrain PID�޷�ѡ��
/// @param new_max ���ֵ
/// @param new_min ��Сֵ(ֻ��PID����޷�ʹ��)
void PID_Constrain_Config(PIDConfig_t* PIDConfig,PID_Constrain_Config_t PID_Constrain,PIDElem_t new_max,PIDElem_t new_min)
{
	switch (PID_Constrain)
	{
	case PID_P_Constrain:
		PIDConfig->PMax = new_max;
		break;
	case PID_I_Constrain:
		PIDConfig->IMax = new_max;
		break;
	case PID_D_Constrain:
		PIDConfig->DMax = new_max;
		break;
	case PID_PID_Constrain:
		PIDConfig->PIDMax = new_max;
		PIDConfig->PIDMin = new_min;
		break;
	}
}
#ifdef TEMP_MUL
#undef Mul
#undef TEMP_MUL
#endif