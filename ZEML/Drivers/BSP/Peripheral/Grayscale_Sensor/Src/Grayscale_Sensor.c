/**
  ******************************************************************************
  * @file   
  * @brief  
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* includes --------------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "Grayscale_Sensor.h"
/* Exported types 类型定义------------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
/* Exported constants 常量定义--------------------------------------------------------*/

/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/

/**
 * @brief 灰度传感器初始化函数
 * @param GaryX:传入传感器结构体
 * @return count :找到设备存在的地址数量
*/
uint8_t Gray_Init (Gary_HandleTypeDef *GaryX)
{
  uint8_t count = 0;

  /* 清空已有设备地址 */
  for (uint8_t i = 0; i < 128; i++)
  {
    GaryX->addr_tab[i] = 0;
  }
  /*扫描传感器存在的所有地址*/
  for (uint8_t i = 1; i < 128; i++)
  {
    /* 读取设备地址内容 */
    GaryX->GarySta = HAL_I2C_IsDeviceReady(&hi2c1,(uint16_t)(i<<1),2,100);
    if (GaryX->GarySta != HAL_OK)
    {
      /*没有读取到，归零*/
      GaryX->addr_tab[i] = 0;
    }
    else
    {
      /*读取到了就将地址存起来，并且记录找到的地址数*/
      GaryX->addr_tab[count] = i;
      count += 1;
    }
  }
  return count;
}

/**
 * @brief PING检测函数
 * @param GaryX:传入传感器结构体
 * @retval _StatusTypeDef
*/
_StatusTypeDef PING_check (Gary_HandleTypeDef *GaryX)
{
  GaryX->cmd = GRAY_PING;

  HAL_I2C_Mem_Read(&hi2c1,GRAY_ADDR_DEF << 1,GaryX->cmd,1,&GaryX->Ping_addr,1,100);
  
  if (GaryX->Ping_addr == GRAY_PING_OK)
  {
    /* code */
    return _SUCCESS;
  }
  else
  {
    return _ERROR;
  }
  
}
/**
 * @brief 数字数据读取模式，每次读取一个8bit的数据
 * @param GaryX:传入传感器结构体
 * @retval None
*/
void Gary_Read_8bit (Gary_HandleTypeDef *GaryX)
{
  GaryX->cmd = GRAY_DIGITAL_MODE;

  HAL_I2C_Master_Transmit(&hi2c1,GRAY_ADDR_DEF << 1,&GaryX->cmd,1,100);

  HAL_I2C_Master_Receive(&hi2c1,GRAY_ADDR_DEF << 1,&GaryX->receive_8bit,1,100);

}

/**
 * @brief 模拟数据模式，循环读取8个探头的模拟数据
 * @param GaryX:传入传感器结构体
 * @retval None
*/
void Gary_Read_8OC (Gary_HandleTypeDef *GaryX)
{
  GaryX->cmd = GRAY_ANALOG_MODE;

  HAL_I2C_Master_Transmit(&hi2c1,GRAY_ADDR_DEF << 1, &GaryX->cmd,1,100);
  
  HAL_I2C_Master_Receive(&hi2c1,GRAY_ADDR_DEF << 1,GaryX->OC,8,100);

}



