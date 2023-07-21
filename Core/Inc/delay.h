/**
  ******************************************************************************
  * @file   delay.h
  * @brief  提供延时函数声明
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
#ifndef __delay_h__
#define __delay_h__
/* includes --------------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
/* Private includes 非官方头文件声明----------------------------------------------------------*/
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/

void HAL_Delay_us_init(uint8_t SYSCLK);
void HAL_Delay_us(uint32_t us);
void TIM_Delay_us(uint32_t us);
void TIM_Delay_ms(uint16_t ms);


#endif
