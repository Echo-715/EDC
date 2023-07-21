/**
  ******************************************************************************
  * @file   delay.c
  * @brief  提供微秒级延时函数，该函数基于SysTick计时方式实现。
  ******************************************************************************
  * @attention  
  * 
  *  None
  *
  ******************************************************************************
**/
/* includes --------------------------------------------------------------------------*/
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "delay.h"
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
uint32_t fac_us;

extern TIM_HandleTypeDef htim1;
/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/

 /**
  * @brief  微秒延时初始化
  * @param  SYSCLK：系统时钟
  * @retval None
  */
void HAL_Delay_us_init(uint8_t SYSCLK)
{
     fac_us=SYSCLK; 
}

 /**
  * @brief 微秒延时函数，通过系统计时器实现
  * @param  us:延时时间
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
  * @brief 通过TIM定时实现us级别延时
  * @param  us：延时时间
  * @retval None
  */
void TIM_Delay_us(uint32_t us)
{

    uint16_t  differ = 0xffff-us-5;
    /*设置定时器2的技术初始值*/
  __HAL_TIM_SetCounter(&htim1,differ);
  /*开启定时器*/
  HAL_TIM_Base_Start(&htim1);

  while( differ<0xffff-5)
    {
        differ = __HAL_TIM_GetCounter(&htim1);
    };
 /*关闭定时器*/
  HAL_TIM_Base_Stop(&htim1);
}

 /**
  * @brief  普通定时器TIM实现ms级别延时,可以用HAL_Delay()替代
  * @param  ms：延时时间
  * @retval None
  */
void TIM_Delay_ms(uint16_t ms)
{
    uint32_t i;
    for(i=0;i<ms;i++) user_delaynus_tim(1000);
}
