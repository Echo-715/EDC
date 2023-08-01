/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "Key.h"
#include "OLED.h"
#include "Buzzer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
StateTypeDef link;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task_UIHandle;
osThreadId Task_InfoHandle;
osThreadId Task_DetectionHandle;
osThreadId Task_LEDHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void UI(void const * argument);
void Info(void const * argument);
void Detection(void const * argument);
void LED(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task_UI */
  osThreadDef(Task_UI, UI, osPriorityNormal, 0, 128);
  Task_UIHandle = osThreadCreate(osThread(Task_UI), NULL);

  /* definition and creation of Task_Info */
  osThreadDef(Task_Info, Info, osPriorityHigh, 0, 128);
  Task_InfoHandle = osThreadCreate(osThread(Task_Info), NULL);

  /* definition and creation of Task_Detection */
  osThreadDef(Task_Detection, Detection, osPriorityLow, 0, 128);
  Task_DetectionHandle = osThreadCreate(osThread(Task_Detection), NULL);

  /* definition and creation of Task_LED */
  osThreadDef(Task_LED, LED, osPriorityLow, 0, 128);
  Task_LEDHandle = osThreadCreate(osThread(Task_LED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_UI */
/**
  * @brief  Function implementing the Task_UI thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_UI */
void UI(void const * argument)
{
  /* USER CODE BEGIN UI */
  uint8_t pages;
  int time_now;

  /* Infinite loop */
  for(;;)
  {
    pages = Allkey.Memu;
    time_now = HAL_GetTick();
    switch (pages )
    {
    case 0:
      /* code */
      OLED_ShowString(1,6,"EDC_Car");
          if (Per.CAN_state != time_now)
    {
      link.CAN_state = 0;
    }
    else
    {
      OLED_ShowString(2,2,"CAN_link");
    }
    
    if (Per.IMU_state != 0x020)
    {
      /* code */
      link.IMU_state = 0;
    }
    else
    {
      OLED_ShowString(2,8,"IMU_link");
    }
    if (Per.USART2_state != time_now)
    {
      /* code */
      link.USART2_state = 0;
    }
    else
    {
      OLED_ShowString(3,2,"USART_link");
    }

      break;
    case 1:
      /* code */
      OLED_ShowString(1,1,"MOD:");
      OLED_ShowNum(1,6,Allkey.key1.Flag,1);
      if (Allkey.key2.Flag)
      {
          /* code */
        OLED_ShowString(1,8,"running!");
      }
      break;
    default:
      break;
    }

    osDelay(1);

  }
  /* USER CODE END UI */
}

/* USER CODE BEGIN Header_Info */
/**
* @brief Function implementing the Task_Info thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Info */
void Info(void const * argument)
{
  /* USER CODE BEGIN Info */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Info */
}

/* USER CODE BEGIN Header_Detection */
/**
* @brief Function implementing the Task_Detection thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Detection */
void Detection(void const * argument)
{
  /* USER CODE BEGIN Detection */
  
  /* Infinite loop */
  for(;;)
  {
    
    if ((!KEY1_RESET)||(!KEY2_RESET))
    {
      /* code */
      osDelay(5);
      Key_Prompt();
    }
    osDelay(1);
    Key_Scan(&Allkey);

    

    osDelay(1);
  }
  /* USER CODE END Detection */
}

/* USER CODE BEGIN Header_LED */
/**
* @brief Function implementing the Task_LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED */
void LED(void const * argument)
{
  /* USER CODE BEGIN LED */
  /* Infinite loop */
  for(;;)
  {
	
    osDelay(1);
  }
  /* USER CODE END LED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

