/**
  ******************************************************************************
  * @file   delay.c
  * @brief  �ṩ΢�뼶��ʱ�������ú�������SysTick��ʱ��ʽʵ�֡�
  ******************************************************************************
  * @attention  
  * 
  *  None
  *
  ******************************************************************************
**/
/* includes --------------------------------------------------------------------------*/
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
#include "delay.h"
/* Exported types ���Ͷ���------------------------------------------------------------*/
/* Exported constants ��������--------------------------------------------------------*/
uint32_t fac_us;

extern TIM_HandleTypeDef htim1;
/* Exported macro �궨��------------------------------------------------------------*/
/* Exported functions prototypes ��������---------------------------------------------*/

 /**
  * @brief  ΢����ʱ��ʼ��
  * @param  SYSCLK��ϵͳʱ��
  * @retval None
  */
void HAL_Delay_us_init(uint8_t SYSCLK)
{
     fac_us=SYSCLK; 
}

 /**
  * @brief ΢����ʱ������ͨ��ϵͳ��ʱ��ʵ��
  * @param  us:��ʱʱ��
  * @retval None
  */
void HAL_Delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told,tnow,tcnt=0;
    uint32_t reload=SysTick->LOAD;
    ticks=us*fac_us; 
    told=SysTick->VAL;
    while(1)
    {
        tnow=SysTick->VAL;
        if(tnow!=told)
        {
            if(tnow<told)tcnt+=told-tnow;
            else tcnt+=reload-tnow+told;
            told=tnow;
            if(tcnt>=ticks)break; 
        }
    };
}

 /**
  * @brief ͨ��TIM��ʱʵ��us������ʱ
  * @param  us����ʱʱ��
  * @retval None
  */
void TIM_Delay_us(uint32_t us)
{

    uint16_t  differ = 0xffff-us-5;
    /*���ö�ʱ��2�ļ�����ʼֵ*/
  __HAL_TIM_SetCounter(&htim1,differ);
  /*������ʱ��*/
  HAL_TIM_Base_Start(&htim1);

  while( differ<0xffff-5)
    {
        differ = __HAL_TIM_GetCounter(&htim1);
    };
 /*�رն�ʱ��*/
  HAL_TIM_Base_Stop(&htim1);
}

 /**
  * @brief  ��ͨ��ʱ��TIMʵ��ms������ʱ,������HAL_Delay()���
  * @param  ms����ʱʱ��
  * @retval None
  */
void TIM_Delay_ms(uint16_t ms)
{
    uint32_t i;
    for(i=0;i<ms;i++) user_delaynus_tim(1000);
}
