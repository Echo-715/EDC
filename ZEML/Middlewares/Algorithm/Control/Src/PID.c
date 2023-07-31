/**
  ******************************************************************************
  * @file   
  * @brief  
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/

/* includes --------------------------------------------------------------------------*/
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
#include "Motor.h"
#include "PID.h" 
/* Exported types ���Ͷ���------------------------------------------------------------*/
PID_parameter_Typedef Chassis_PID;
PID_parameter_Typedef Location_PID;
/* Exported constants ��������--------------------------------------------------------*/
/* Exported macro �궨��------------------------------------------------------------*/
/* Exported functions prototypes ��������---------------------------------------------*/

 /**
  * @brief PID��ʼ��
  * @param PID��PID�ṹ��
  * @retval None
  */
void PID_Init (PID_parameter_Typedef *PID,float Kp,float Ki,float Kd,float PIDmax,float Imax,float Dmax)
{
  PID->Proportion_Coefficient = Kp;
  PID->Integration_Coefficient = Ki;
  PID->Differentiation_Coefficient = Kd;

  PID->PID_FailMaxOutPut = PIDmax;
  PID->Integration_MaxOutPut = Imax;
  PID->Differentiation_MaxOutPut = Dmax;
}

 /**
  * @brief �ٶȻ�PID�����㷨
  * @param PID��PID�ṹ��
  * @param Expecat_Value: ����ֵ
  * @param Actual_Value�� ʵ��ֵ
  * @retval PID�������
  */
int SpeedPID_Process (PID_parameter_Typedef *PID,int Expecat_Value, int Actual_Value )
{
    float PID_OutPut = 0; 
    float   P_OUT = 0, I_OUT = 0, D_OUT = 0;
    float   Integration = 0, Differentiation = 0;
    float   Error = 0;

    Error = Expecat_Value - Actual_Value;
    PID->LastError = Error;

    Integration += Error;
    Differentiation = Error - PID->LastError;

    Integration = PID_LimitMax(Integration,PID->Integration_MaxOutPut);
    Differentiation = PID_LimitMax(Differentiation,PID->Differentiation_MaxOutPut);

    P_OUT = PID->Proportion_Coefficient * Error;
    I_OUT = PID->Integration_Coefficient * Integration;
    D_OUT = PID->Differentiation_Coefficient * Differentiation;
			
	
    PID_OutPut = P_OUT + I_OUT + D_OUT;
    PID_OutPut = PID_LimitMax(PID_OutPut,PID->PID_FailMaxOutPut);

    return PID_OutPut;
}

 /**
  * @brief λ�û�PID�����㷨
  * @param PID��PID�ṹ��
  * @param Expecat_Value: ����ֵ
  * @param Actual_Value�� ʵ��ֵ
  * @retval PID�������
  */
int LocationPID_Process (PID_parameter_Typedef *PID,int Expecat_Value, int Actual_Value )
{
    float PID_OutPut = 0; 
    float   P_OUT = 0, I_OUT = 0, D_OUT = 0;
    float   Integration = 0, Differentiation = 0;
    float   Error = 0;

    Error = Expecat_Value - Actual_Value;
    PID->LastError = Error;

    Integration += Error;
    Differentiation = Error - PID->LastError;

    Integration = PID_LimitMax(Integration,PID->Integration_MaxOutPut);
    Differentiation = PID_LimitMax(Differentiation,PID->Differentiation_MaxOutPut);

    P_OUT = PID->Proportion_Coefficient * Error;
    I_OUT = PID->Integration_Coefficient * Integration;
    D_OUT = PID->Differentiation_Coefficient * Differentiation;
		Error  = PID_LimitMax(Error,PID->Eorror_MaxOutPut);	
	
    PID_OutPut = P_OUT + I_OUT + D_OUT;
    PID_OutPut = PID_LimitMax(PID_OutPut,PID->PID_FailMaxOutPut);

    return PID_OutPut;
}

 /**
  * @brief PID�����޷�
  * @param Input��������Ҫ���޷���ֵ
  * @param Max: ��С�����ֵ
  * @note ���Ƶ���С���ֵΪMAX������ֵ
  * @retval ���ش���������ֵ
  */
float PID_LimitMax(float Input,float Max)   
{                          
	if (Input > Max)       
    {                      
        Input = Max;       
    }                      
    else if (Input < -Max) 
    {                      
        Input = -Max;      
    }
	return Input;
}

