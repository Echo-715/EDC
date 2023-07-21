/**
  ******************************************************************************
  * @file   Buzzer.c
  * @brief  提供蜂鸣器使用的各种声调API
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* includes --------------------------------------------------------------------------*/
#include "tim.h"
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "Buzzer.h"
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
int16_t random[];
/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/
/**
 * @addtogroup 蜂鸣器基本操作
 * @{
*/

 /**
  * @brief 音量调节
  * @param Pluse: 占空比大小，改变蜂鸣器的音量
  * @retval None
  */
void Buzzer_Volume (int16_t Pluse)
{ 
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,Pluse);
}

/**
 * @brief 通过改变PWM的频率从而改变蜂鸣器的音调
 * @param PSC:TIM的时钟预分频数值
 * @note 输出频率 f= 系统频率（72M）/[(PSC+1)*(ARR+1)]  默认设置ARR=1K; => 输出频率：f=72000/PSC+1
 * @retval None
*/
void Buzzer_Tonal (int16_t PSC)
{
  
  __HAL_TIM_SET_PRESCALER(&htim3,PSC);

}
 /**
  * @brief 关闭声音
  * @param None
  * @retval None
  */
void Buzzer_OFF ()
{ 
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,Z0);
}
 /**
  * @ }
 */

/**
 * @addtogroup 常用提示音
 * @{
*/

 /**
  * @brief 用于开机提示
  * @param None
  * @retval None
  */
void Boot_Prompt ()
{
  int16_t DoDoDU[]={M_do,H_mi,M_sol,M_re,H_do}; /*音乐数组*/
  int Length = sizeof(DoDoDU)/sizeof(DoDoDU[0]);

  for (uint8_t i = 0; i < Length; i++) /*蜂鸣器播放音乐*/
  {
    /* code */
    Buzzer_Volume(200);
    Buzzer_Tonal(DoDoDU[i]);
    HAL_Delay(200);
  }
  Buzzer_OFF();

}
 /**
  * @ }
 */
