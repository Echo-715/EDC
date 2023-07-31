/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_RxHeaderTypeDef RxMessage;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_4TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_5TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = ENABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

	CAN_FilterTypeDef filter;
  
	filter.FilterBank=1;//ÂË²¨Æ÷±àºÅ
	filter.FilterMode=CAN_FILTERMODE_IDMASK;//ÑÚÂëÄ£Ê½
	filter.FilterScale=CAN_FILTERSCALE_32BIT;
	filter.FilterIdHigh=0x0000;
	filter.FilterIdLow=0x0000;
	filter.FilterMaskIdHigh=0x0000;
	filter.FilterMaskIdLow=0x0000;
	filter.FilterFIFOAssignment=CAN_FILTER_FIFO0;//FIFO0
	filter.FilterActivation=ENABLE;
  
  if(HAL_CAN_ConfigFilter(&hcan,&filter)!=HAL_OK)
	{
		Error_Handler();
	}	
  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */
    __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void Message_buffer(CAN_RxHeaderTypeDef* RxMessage, uint8_t RxData[8],uint8_t buf[][8])
{
	static uint8_t i;
	
	if(0x201 == RxMessage->StdId)	
	{
		for(i = 0; i < 6; i++)	
			buf[0][i] = RxData[i];
	}
	else if(0x202 == RxMessage->StdId)
	{
		for(i = 0; i < 6; i++)
			buf[1][i] =RxData[i];
	}
	else if(0x203 == RxMessage->StdId)
	{
		for(i = 0; i < 6; i++)
			buf[2][i] =RxData[i];
	}
	else if(0x204 == RxMessage->StdId)
	{
		for(i = 0; i < 6; i++)
			buf[3][i] = RxData[i];
	}
	
	else if(0x205 == RxMessage->StdId)  
	{
		for(i = 0; i < 6; i++)	
			buf[4][i] = RxData[i];  
	}
	else if(0x206 == RxMessage->StdId)  
	{
		for(i = 0; i < 6; i++)
			buf[5][i] = RxData[i];  
	}
	
	else if(0x207 == RxMessage->StdId)
	{
		for(i = 0; i < 6; i++)		
			buf[6][i] = RxData[i];
	}		
}
/* USER CODE END 1 */
