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
/* Exported types 类型定义------------------------------------------------------------*/
extern TIM_HandleTypeDef htim8;
MotorTyprDef Motor;
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/

/**
* @brief  设置TB6612驱动电机正反转
* @param  direction：旋转方向选择，0为反传，1为正转
* @param  Motor:电机的ID
* @return None
*/
void Positive_Inversion (uint8_t direction , Motor_Numb Motor)
{
  switch (Motor)
  {
  case Motor_1 :
    if (direction)
    {
      HAL_GPIO_WritePin(MOTOR1_GPIO_1,MOTOR1_PIN_1,GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR1_GPIO_2,MOTOR1_PIN_2,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(MOTOR1_GPIO_1,MOTOR1_PIN_1,GPIO_PIN_SET);
      HAL_GPIO_WritePin(MOTOR1_GPIO_2,MOTOR1_PIN_2,GPIO_PIN_RESET);
    }
    break;
  
  case Motor_2 :
    if (direction)
    {
      HAL_GPIO_WritePin(MOTOR2_GPIO_1,MOTOR2_PIN_1,GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR2_GPIO_2,MOTOR2_PIN_2,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(MOTOR2_GPIO_1,MOTOR2_PIN_1,GPIO_PIN_SET);
      HAL_GPIO_WritePin(MOTOR2_GPIO_2,MOTOR2_PIN_2,GPIO_PIN_RESET);
    }
    break;
  case Motor_3 :
    if (direction)
    {
      HAL_GPIO_WritePin(MOTOR3_GPIO_1,MOTOR3_PIN_1,GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR3_GPIO_2,MOTOR3_PIN_2,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(MOTOR3_GPIO_1,MOTOR3_PIN_1,GPIO_PIN_SET);
      HAL_GPIO_WritePin(MOTOR3_GPIO_2,MOTOR3_PIN_2,GPIO_PIN_RESET);
    }
    break;

  case Motor_4:
    if (direction)
    {
      HAL_GPIO_WritePin(MOTOR4_GPIO_1,MOTOR4_PIN_1,GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR4_GPIO_2,MOTOR4_PIN_2,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(MOTOR4_GPIO_1,MOTOR4_PIN_1,GPIO_PIN_SET);
      HAL_GPIO_WritePin(MOTOR4_GPIO_2,MOTOR4_PIN_2,GPIO_PIN_RESET);
    }
    break;
  
  }
  
}


/**
* @brief  霍尔编码器数值读取
* @param  TIMx：该电机所用的计时器
* @return pulse_count,脉冲数值->计时器计数值
*/
int Read_Encoder(TIM_HandleTypeDef * TIMx)
{
  int pulse_count;
  pulse_count = __HAL_TIM_GET_COUNTER(TIMx); /*读取脉冲数*/

  if(pulse_count>0xefff)
  {
    pulse_count=pulse_count-0xffff; /*转换计数值为方向值，>0为正转，<0为反转*/ 
  }

  __HAL_TIM_SET_COUNTER(TIMx,0);
  return pulse_count;
}

/**
* @brief  获取编码器电机速度
* @param  TIMx：该电机所用的计时器
* @return Velocity,编码器速度，单位：M/S
*/
float Get_Velocity (TIM_HandleTypeDef * TIMx)
{
  float Velocity;
  Velocity = Read_Encoder(TIMx)/1560.0f;
  return Velocity;
}

/**
* @brief  电机输出
* @param  Motor:电机编号
* @param  Output:电机输出
* @return None
*/
void Motor_Output (Motor_Numb Motor,float *Output)
{
  switch (Motor)
  {
  case Motor_1:
    /* code */
    if(Output[0] > 0)
    {
      Positive_Inversion(1,Motor_1);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,Output[0]);
    }
    else if (Output[0] < 0)
    {
      Positive_Inversion(0,Motor_1);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,-Output[0]);
    }
    break;

  case Motor_2:
    /* code */
    if(Output[1] > 0)
    {
      Positive_Inversion(1,Motor_2);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,Output[1]);
    }
    else if (Output[1] < 0)
    {
      Positive_Inversion(0,Motor_2);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,-Output[1]);
    }
    break;

  case Motor_3:
    /* code */
    if(Output[2] > 0)
    {
      Positive_Inversion(1,Motor_3);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,Output[2]);
    }
    else if (Output[2] < 0)
    {
      Positive_Inversion(0,Motor_3);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,-Output[2]);
    }
    break;

  case Motor_4:
    /* code */
    if(Output[3] > 0)
    {
      Positive_Inversion(1,Motor_4);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,Output[3]);
    }
    else if (Output[3] < 0)
    {
      Positive_Inversion(0,Motor_4);
      __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,-Output[3]);
    }
    break;
  
  default:
    break;
  }

  
}


