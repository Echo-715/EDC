/**
  ******************************************************************************
  * @file    OLED.h
  * @brief   提供使用OLED屏幕时的函数声明以及宏定义
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/

/*Define to prevent recursive inclusion 防止递归包含*/
#ifndef __OLED_H__
#define __OLED_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "i2c.h"
/* Private includes 非官方头文件声明----------------------------------------------------------*/
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
#define OLED0561_ADD	0x78  /**/
#define COMM				  0x00  /**/
#define DATA			    0x40  /**/ 

/**
  * @brief  OLED功能配置函数
  * @param  Addr 写入的地址
  * @param  Data 写入的数据
  * @retval None
  */
#define OLED_Write(Addr,Data) HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,Addr,I2C_MEMADD_SIZE_8BIT,Data,1,100);

/* Exported functions prototypes 函数声明---------------------------------------------*/

/**
  * @addtogroup OLED各类显示操作API
  * @{
  */
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize);/*显示字符串*/
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t N);/*显示单个中文字符*/
void OLED_ShowCN_STR(uint8_t x , uint8_t y , uint8_t begin , uint8_t num);/*显示中文字符串*/
void OLED_ShowCN2(uint8_t x, uint8_t y, uint8_t N);
void OLED_ShowCN_STR2(uint8_t x , uint8_t y , uint8_t begin , uint8_t num);
void OLED_ShowCN3(uint8_t x, uint8_t y, uint8_t N);
void OLED_ShowCN_STR3(uint8_t x , uint8_t y , uint8_t begin , uint8_t num);
/**
  * @}
  */

/**
  * @addtogroup OLED基本设置以及初始化API
  * @{
  */
void OLED_DataWrite(uint8_t IIC_Data);/*OLED数据信息写入*/

void OLED_Init(void);/*OLED初始化*/

void OLED_Fill(uint8_t fill_Data);/*全屏填充操作*/
void OLED_SetPos(uint8_t x, uint8_t y);/*起始点位置设置*/
void OLED_CLS(void);/*清空所有显示内容*/
void OLED_ON (void);/*开启OLED*/
void OLED_OFF (void);/*关闭OLED*/
/**
  * @}
  */

#endif

