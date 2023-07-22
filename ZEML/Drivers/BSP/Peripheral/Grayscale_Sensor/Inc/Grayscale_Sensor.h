/**
  ******************************************************************************
  * @file   Grayscale_Sensor.h
  * @brief  提供灰度传感器的常用地址，模式选择，操作API
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/

#ifndef __GRAYSCALE_SENSOR_H_
#define __GRAYSCALE_SENSOR_H_
/* includes --------------------------------------------------------------------------*/
#include <stdint.h>
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "ZEML_def.h"
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/


/* 默认地址 */
#define GRAY_ADDR_DEF 0x4C

/**
 * @addtogroup
 * 灰度传感器常用命令地址
*/
/**
 * @{
*/
/*PING检测*/
#define GRAY_PING 0xAA
/*PING检测通过*/
#define GRAY_PING_OK 0x66
#define GRAY_PING_RSP GRAY_PING_OK

/* 开启开关数据模式 */
#define GRAY_DIGITAL_MODE 0xDD

/* 开启连续读取模拟数据模式 */
#define GRAY_ANALOG_BASE 0xB0
#define GRAY_ANALOG_MODE  (GRAY_ANALOG_BASE + 0)

/* 传感器归一化寄存器(v3.6及之后的固件) */
#define GRAY_ANALOG_NORMALIZE 0xCF

/* 循环读取单个探头模拟数据 n从1开始到8 */
#define GRAY_ANALOG(n) (_GRAY_ANALOG_BASE_ + (n))

/* 黑色滞回比较参数操作 */
#define GRAY_CALIBRATION_BLACK 0xD0
/* 白色滞回比较参数操作 */
#define GRAY_CALIBRATION_WHITE 0xD1

/* 读取错误信息 */
#define GRAY_ERROR 0xDE

/* 设备软件重启 */
#define GRAY_REBOOT 0xC0

/* 读取固件版本号 */
#define GRAY_FIRMWARE 0xC1

/* 设置设备I2C地址 */
#define GRAY_CHANGE_ADDR 0xAD

/* 广播重置地址所需要发的数据 */
 #define GRAY_BROADCAST_RESET "\xB8\xD0\xCE\xAA\xBF\xC6\xBC\xBC"
/**
 * @}
*/

/*设置所需探头的模拟信号(CE: channel enable)*/
#define GRAY_ANALOG_CHANNEL_ENABLE 0xCE
#define GRAY_ANALOG_CH_EN_1 (0x1 << 0)
#define GRAY_ANALOG_CH_EN_2 (0x1 << 1)
#define GRAY_ANALOG_CH_EN_3 (0x1 << 2)
#define GRAY_ANALOG_CH_EN_4 (0x1 << 3)
#define GRAY_ANALOG_CH_EN_5 (0x1 << 4)
#define GRAY_ANALOG_CH_EN_6 (0x1 << 5)
#define GRAY_ANALOG_CH_EN_7 (0x1 << 6)
#define GRAY_ANALOG_CH_EN_8 (0x1 << 7)
#define GRAY_ANALOG_CH_EN_ALL (0xFF)

/**
 * @brief 灰度传感器结构体
*/
typedef struct 
{
  HAL_StatusTypeDef GarySta; /*传感器状态*/

  uint8_t OC[8];   /*每个探头的数据*/

  uint8_t addr_tab[128];   /*初始化扫描设备地址*/
  
  uint8_t receive_8bit;   /*8探头的字节数据*/

  uint8_t Ping_addr;    /*ping检测返回地址*/

  uint8_t cmd; /*用户自定义命令*/

}Gary_HandleTypeDef;

/* Exported functions prototypes 函数声明---------------------------------------------*/
/**
 * @brief 从I2C得到的8位的数字信号的数据 读取第n位的数据
 * @param sensor_value 数字IO的数据
 * @param n 第1位从1开始, n=1 是传感器的第一个探头数据, n=8是最后一个
 * @return
 */
#define GET_NTH_BIT(sensor_value, nth_bit) (((sensor_value) >> ((nth_bit)-1)) & 0x01)


/**
 * @brief 从一个变量分离出所有的bit
 */
#define SEP_ALL_BIT(sensor_value, val1, val2, val3, val4, val5, val6, val7, val8) \
do {                                                                              \
val1 = GET_NTH_BIT(sensor_value, 1);                                              \
val2 = GET_NTH_BIT(sensor_value, 2);                                              \
val3 = GET_NTH_BIT(sensor_value, 3);                                              \
val4 = GET_NTH_BIT(sensor_value, 4);                                              \
val5 = GET_NTH_BIT(sensor_value, 5);                                              \
val6 = GET_NTH_BIT(sensor_value, 6);                                              \
val7 = GET_NTH_BIT(sensor_value, 7);                                              \
val8 = GET_NTH_BIT(sensor_value, 8);                                              \
} while(0)


uint8_t Gray_Init (Gary_HandleTypeDef *GaryX); /*传感器初始化*/

_StatusTypeDef PING_check (Gary_HandleTypeDef *GaryX);/*ping检测函数*/

void Gary_Read_8bit (Gary_HandleTypeDef *GaryX);/*数据读取模式*/

void Gary_Read_8OC (Gary_HandleTypeDef *GaryX);/*连续读取8探头数据*/


#endif /* INC_GW_GRAYSCALE_SENSOR_H_ */
