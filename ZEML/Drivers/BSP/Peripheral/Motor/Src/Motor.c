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
/* Exported types ���Ͷ���------------------------------------------------------------*/
extern TIM_HandleTypeDef htim8;
MotorTyprDef Motor;
/* Exported constants ��������--------------------------------------------------------*/
/* Exported macro �궨��------------------------------------------------------------*/
/* Exported functions prototypes ��������---------------------------------------------*/

/**
* @brief  ����TB6612�����������ת
* @param  direction����ת����ѡ��0Ϊ������1Ϊ��ת
* @param  Motor:�����ID
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
* @brief  ������������ֵ��ȡ
* @param  TIMx���õ�����õļ�ʱ��
* @return pulse_count,������ֵ->��ʱ������ֵ
*/
int Read_Encoder(TIM_HandleTypeDef * TIMx)
{
  int pulse_count;
  pulse_count = __HAL_TIM_GET_COUNTER(TIMx); /*��ȡ������*/

  if(pulse_count>0xefff)
  {
    pulse_count=pulse_count-0xffff; /*ת������ֵΪ����ֵ��>0Ϊ��ת��<0Ϊ��ת*/ 
  }

  __HAL_TIM_SET_COUNTER(TIMx,0);
  return pulse_count;
}

/**
* @brief  ��ȡ����������ٶ�
* @param  TIMx���õ�����õļ�ʱ��
* @return Velocity,�������ٶȣ���λ��M/S
*/
float Get_Velocity (TIM_HandleTypeDef * TIMx)
{
  float Velocity;
  Velocity = Read_Encoder(TIMx)/1560.0f;
  return Velocity;
}

/**
* @brief  ������
* @param  Motor:������
* @param  Output:������
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


