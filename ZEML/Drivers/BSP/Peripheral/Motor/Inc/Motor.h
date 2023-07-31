/**
  ******************************************************************************
  * @file   
  * @brief  
  ******************************************************************************
  * @attention
  * 
  *  None
  *   橡胶轮周长:20.42035224cm
  *   编码器线数：13线
  *   电机减速比：1：30
  *   ->得到轮子的速度(近似瞬时)
  *   ->V = 10ms内得到的脉冲数/3.18557494944 单位:M/S
  *
  ******************************************************************************  
**/
/* includes --------------------------------------------------------------------------*/
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "main.h"
/* Exported types 类型定义------------------------------------------------------------*/
typedef enum
{

  Motor_1 = 1,
  Motor_2 = 2,
  Motor_3 = 3,
  Motor_4 = 4,

} Motor_Numb;

typedef struct 
{
  /* data */
  int velocity[4];
  float output[4]; 

}MotorTyprDef;

extern MotorTyprDef Motor;
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
  #define CHASSISPID_SPEED_KP   4
  #define CHASSISPID_SPEED_KI   0
  #define CHASSISPID_SPEED_KD   0
  #define CHASSISPID_SPEED_PIDMAX   16384
  #define CHASSISPID_SPEED_IMAX     5000
  #define CHASSISPID_SPEED_DMAX     5000

#define MOTOR1_GPIO_1  GPIOC
#define MOTOR1_PIN_1   GPIO_PIN_0

#define MOTOR1_GPIO_2  GPIOC
#define MOTOR1_PIN_2   GPIO_PIN_1

#define MOTOR2_GPIO_1  GPIOC
#define MOTOR2_PIN_1   GPIO_PIN_2

#define MOTOR2_GPIO_2  GPIOC
#define MOTOR2_PIN_2   GPIO_PIN_3

#define MOTOR3_GPIO_1  GPIOB
#define MOTOR3_PIN_1   GPIO_PIN_12

#define MOTOR3_GPIO_2  GPIOB
#define MOTOR3_PIN_2   GPIO_PIN_13

#define MOTOR4_GPIO_1  GPIOB
#define MOTOR4_PIN_1   GPIO_PIN_14

#define MOTOR4_GPIO_2  GPIOB
#define MOTOR4_PIN_2   GPIO_PIN_15
/* Exported functions prototypes 函数声明---------------------------------------------*/

void Positive_Inversion (uint8_t direction , Motor_Numb Motor);
int Read_Encoder(TIM_HandleTypeDef * TIMx);
float Get_Velocity (TIM_HandleTypeDef * TIMx);
void Motor_Output (Motor_Numb Motor,float *Output);
