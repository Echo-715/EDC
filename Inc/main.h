/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct 
{
  /* data */
  uint8_t data_can[8];
  uint8_t data_usart[8];
  uint8_t data_vision[8];
}SysDataTypeDef;

typedef struct 
{
    /* data */
    struct 
    {
        /* data */
        int16_t X;
        int16_t Y;
        
    }Num[20];
        
}Poinset_TypeDef;

extern Poinset_TypeDef frame;
extern SysDataTypeDef Receive;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define LED1_SET  		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 100)
#define LED2_SET			__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 100)
#define LED3_SET			__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 100)

#define LED1_RESET  		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0)
#define LED2_RESET			__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 0)
#define LED3_RESET			__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 0)
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define KEY1_RESET  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define KEY2_RESET  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
