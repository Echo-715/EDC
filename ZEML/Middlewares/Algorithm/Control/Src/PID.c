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
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "Motor.h"
#include "PID.h" 
/* Exported types 类型定义------------------------------------------------------------*/
PID_parameter_Typedef Chassis_PID;
PID_parameter_Typedef Location_PID;
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/

 /**
  * @brief PID初始化
  * @param PID：PID结构体
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
  * @brief 速度环PID控制算法
  * @param PID：PID结构体
  * @param Expecat_Value: 期望值
  * @param Actual_Value： 实际值
  * @retval PID最终输出
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
  * @brief 位置环PID控制算法
  * @param PID：PID结构体
  * @param Expecat_Value: 期望值
  * @param Actual_Value： 实际值
  * @retval PID最终输出
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
  * @brief PID参数限幅
  * @param Input：输入需要被限幅的值
  * @param Max: 最小和最大值
  * @note 限制的最小最大值为MAX的正负值
  * @retval 返回处理后的输入值
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

