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

#define USE_HAREWARE_I2C 1
#if USE_HAREWARE_I2C
/**
  * @brief  OLED功能配置函数
  * @param  Addr 写入的地址
  * @param  Data 写入的数据
  * @retval None
  */
#define OLED_While(address,data)  HAL_I2C_Mem_Write(&hi2c1,0x78,address,I2C_MEMADD_SIZE_8BIT,data,1,1000)
#else 
/* 引脚定义 */
#define OLED_SCL_PORT       OLED_SCL_GPIO_Port
#define OLED_SCL_PIN        OLED_SCL_Pin
#define OLED_SDA_PORT       OLED_SDA_GPIO_Port
#define OLED_SDA_PIN        OLED_SDA_Pin

/* 宏定义 */
#define OLED_W_SCL(x)   		HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, x)
#define OLED_W_SDA(x)		    HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, x)
#define OLED_GPIO_Init()    
#endif

/* Exported functions prototypes 函数声明---------------------------------------------*/

/**
  * @addtogroup OLED各类显示操作API
  * @{
  */
void OLED_Init(void);                                                                  //OLED初始化
void OLED_Clear(void);                                                                 //OLED清屏
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);                           //OLED显示单个字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);                      //OLED显示字符串
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);      //OLED显示无符号数
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length); //OLED显示有符号数
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);   //OLED显示十六进制数
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);   //OLED显示二进制数
void OLED_ShowCHinese16x16(uint8_t x,uint8_t y,uint8_t num,uint8_t (*buf)[16]);

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

