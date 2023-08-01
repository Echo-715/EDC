/**
  ******************************************************************************
  * @file    OLED.h
  * @brief   �ṩʹ��OLED��Ļʱ�ĺ��������Լ��궨��
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/

/*Define to prevent recursive inclusion ��ֹ�ݹ����*/
#ifndef __OLED_H__
#define __OLED_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "i2c.h"
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
/* Exported types ���Ͷ���------------------------------------------------------------*/
/* Exported constants ��������--------------------------------------------------------*/
/* Exported macro �궨��------------------------------------------------------------*/
#define OLED0561_ADD	0x78  /**/
#define COMM				  0x00  /**/
#define DATA			    0x40  /**/ 

#define USE_HAREWARE_I2C 1
#if USE_HAREWARE_I2C
/**
  * @brief  OLED�������ú���
  * @param  Addr д��ĵ�ַ
  * @param  Data д�������
  * @retval None
  */
#define OLED_While(address,data)  HAL_I2C_Mem_Write(&hi2c1,0x78,address,I2C_MEMADD_SIZE_8BIT,data,1,1000)
#else 
/* ���Ŷ��� */
#define OLED_SCL_PORT       OLED_SCL_GPIO_Port
#define OLED_SCL_PIN        OLED_SCL_Pin
#define OLED_SDA_PORT       OLED_SDA_GPIO_Port
#define OLED_SDA_PIN        OLED_SDA_Pin

/* �궨�� */
#define OLED_W_SCL(x)   		HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, x)
#define OLED_W_SDA(x)		    HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, x)
#define OLED_GPIO_Init()    
#endif

/* Exported functions prototypes ��������---------------------------------------------*/

/**
  * @addtogroup OLED������ʾ����API
  * @{
  */
void OLED_Init(void);                                                                  //OLED��ʼ��
void OLED_Clear(void);                                                                 //OLED����
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);                           //OLED��ʾ�����ַ�
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);                      //OLED��ʾ�ַ���
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);      //OLED��ʾ�޷�����
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length); //OLED��ʾ�з�����
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);   //OLED��ʾʮ��������
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);   //OLED��ʾ��������
void OLED_ShowCHinese16x16(uint8_t x,uint8_t y,uint8_t num,uint8_t (*buf)[16]);

/**
  * @}
  */

/**
  * @addtogroup OLED���������Լ���ʼ��API
  * @{
  */
void OLED_DataWrite(uint8_t IIC_Data);/*OLED������Ϣд��*/

void OLED_Init(void);/*OLED��ʼ��*/

void OLED_Fill(uint8_t fill_Data);/*ȫ��������*/
void OLED_SetPos(uint8_t x, uint8_t y);/*��ʼ��λ������*/
void OLED_CLS(void);/*���������ʾ����*/
void OLED_ON (void);/*����OLED*/
void OLED_OFF (void);/*�ر�OLED*/
/**
  * @}
  */

#endif

