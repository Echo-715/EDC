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

/**
  * @brief  OLED�������ú���
  * @param  Addr д��ĵ�ַ
  * @param  Data д�������
  * @retval None
  */
#define OLED_Write(Addr,Data) HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,Addr,I2C_MEMADD_SIZE_8BIT,Data,1,100);

/* Exported functions prototypes ��������---------------------------------------------*/

/**
  * @addtogroup OLED������ʾ����API
  * @{
  */
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize);/*��ʾ�ַ���*/
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t N);/*��ʾ���������ַ�*/
void OLED_ShowCN_STR(uint8_t x , uint8_t y , uint8_t begin , uint8_t num);/*��ʾ�����ַ���*/
void OLED_ShowCN2(uint8_t x, uint8_t y, uint8_t N);
void OLED_ShowCN_STR2(uint8_t x , uint8_t y , uint8_t begin , uint8_t num);
void OLED_ShowCN3(uint8_t x, uint8_t y, uint8_t N);
void OLED_ShowCN_STR3(uint8_t x , uint8_t y , uint8_t begin , uint8_t num);
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

