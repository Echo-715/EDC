/**
  ******************************************************************************
  * @file   Buzzer.c
  * @brief  �ṩ������ʹ�õĸ�������API
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* includes --------------------------------------------------------------------------*/
#include "tim.h"
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
#include "Buzzer.h"
/* Exported types ���Ͷ���------------------------------------------------------------*/
/* Exported constants ��������--------------------------------------------------------*/
int16_t random[];
/* Exported macro �궨��------------------------------------------------------------*/
/* Exported functions prototypes ��������---------------------------------------------*/
/**
 * @addtogroup ��������������
 * @{
*/

 /**
  * @brief ��������
  * @param Pluse: ռ�ձȴ�С���ı������������
  * @retval None
  */
void Buzzer_Volume (int16_t Pluse)
{ 
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,Pluse);
}

/**
 * @brief ͨ���ı�PWM��Ƶ�ʴӶ��ı������������
 * @param PSC:TIM��ʱ��Ԥ��Ƶ��ֵ
 * @note ���Ƶ�� f= ϵͳƵ�ʣ�72M��/[(PSC+1)*(ARR+1)]  Ĭ������ARR=1K; => ���Ƶ�ʣ�f=72000/PSC+1
 * @retval None
*/
void Buzzer_Tonal (int16_t PSC)
{
  
  __HAL_TIM_SET_PRESCALER(&htim3,PSC);

}
 /**
  * @brief �ر�����
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
 * @addtogroup ������ʾ��
 * @{
*/

 /**
  * @brief ���ڿ�����ʾ
  * @param None
  * @retval None
  */
void Boot_Prompt ()
{
  int16_t DoDoDU[]={M_do,H_mi,M_sol,M_do}; /*��������*/
  int Length = sizeof(DoDoDU)/sizeof(DoDoDU[0]);

  for (uint8_t i = 0; i < Length; i++) /*��������������*/
  {
    /* code */
    Buzzer_Volume(10);
    Buzzer_Tonal(DoDoDU[i]);
    HAL_Delay(250);
  }
  Buzzer_OFF();

}
 /**
  * @ }
 */
