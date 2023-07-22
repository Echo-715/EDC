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
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
#include "Grayscale_Sensor.h"
/* Exported types ���Ͷ���------------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
/* Exported constants ��������--------------------------------------------------------*/

/* Exported macro �궨��------------------------------------------------------------*/
/* Exported functions prototypes ��������---------------------------------------------*/

/**
 * @brief �Ҷȴ�������ʼ������
 * @param GaryX:���봫�����ṹ��
 * @return count :�ҵ��豸���ڵĵ�ַ����
*/
uint8_t Gray_Init (Gary_HandleTypeDef *GaryX)
{
  uint8_t count = 0;

  /* ��������豸��ַ */
  for (uint8_t i = 0; i < 128; i++)
  {
    GaryX->addr_tab[i] = 0;
  }
  /*ɨ�贫�������ڵ����е�ַ*/
  for (uint8_t i = 1; i < 128; i++)
  {
    /* ��ȡ�豸��ַ���� */
    GaryX->GarySta = HAL_I2C_IsDeviceReady(&hi2c1,(uint16_t)(i<<1),2,100);
    if (GaryX->GarySta != HAL_OK)
    {
      /*û�ж�ȡ��������*/
      GaryX->addr_tab[i] = 0;
    }
    else
    {
      /*��ȡ���˾ͽ���ַ�����������Ҽ�¼�ҵ��ĵ�ַ��*/
      GaryX->addr_tab[count] = i;
      count += 1;
    }
  }
  return count;
}

/**
 * @brief PING��⺯��
 * @param GaryX:���봫�����ṹ��
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
 * @brief �������ݶ�ȡģʽ��ÿ�ζ�ȡһ��8bit������
 * @param GaryX:���봫�����ṹ��
 * @retval None
*/
void Gary_Read_8bit (Gary_HandleTypeDef *GaryX)
{
  GaryX->cmd = GRAY_DIGITAL_MODE;

  HAL_I2C_Master_Transmit(&hi2c1,GRAY_ADDR_DEF << 1,&GaryX->cmd,1,100);

  HAL_I2C_Master_Receive(&hi2c1,GRAY_ADDR_DEF << 1,&GaryX->receive_8bit,1,100);

}

/**
 * @brief ģ������ģʽ��ѭ����ȡ8��̽ͷ��ģ������
 * @param GaryX:���봫�����ṹ��
 * @retval None
*/
void Gary_Read_8OC (Gary_HandleTypeDef *GaryX)
{
  GaryX->cmd = GRAY_ANALOG_MODE;

  HAL_I2C_Master_Transmit(&hi2c1,GRAY_ADDR_DEF << 1, &GaryX->cmd,1,100);
  
  HAL_I2C_Master_Receive(&hi2c1,GRAY_ADDR_DEF << 1,GaryX->OC,8,100);

}



