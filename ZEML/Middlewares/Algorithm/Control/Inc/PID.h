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
/* Exported types 类型定义------------------------------------------------------------*/
typedef struct 
{
	/* data */
	float Proportion_Coefficient;   //P
	float Integration_Coefficient;   //I
	float Differentiation_Coefficient; //D
	float LastError;
	
	float Eorror_MaxOutPut;
	float Integration_MaxOutPut;
	float Differentiation_MaxOutPut;
	float PID_FailMaxOutPut;
		
}PID_parameter_Typedef;

typedef struct 
{
    /* data */

		PID_parameter_Typedef ChassisCtrl_SpeedPID;
		PID_parameter_Typedef ChassisCtrl_LocationPID;

}System_PID_TypeDef;

extern PID_parameter_Typedef Chassis_PID;
extern PID_parameter_Typedef Location_PID;
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
#ifndef __PID_Solution_H__
#define	__PID_Solution_H__
/* Exported functions prototypes 函数声明---------------------------------------------*/


void PID_Init (PID_parameter_Typedef *PID,float Kp,float Ki,float Kd,float PIDmax,float Imax,float Dmax);
float PID_LimitMax(float Input,float Max);

int SpeedPID_Process (PID_parameter_Typedef *PID,int Expecat_Value, int Actual_Value );
int LocationPID_Process (PID_parameter_Typedef *PID,int Expecat_Value, int Actual_Value );

#endif
