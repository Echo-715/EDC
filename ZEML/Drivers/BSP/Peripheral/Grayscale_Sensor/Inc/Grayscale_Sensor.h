/**
  ******************************************************************************
  * @file   Grayscale_Sensor.h
  * @brief  �ṩ�Ҷȴ������ĳ��õ�ַ��ģʽѡ�񣬲���API
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
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
#include "ZEML_def.h"
/* Exported types ���Ͷ���------------------------------------------------------------*/
/* Exported constants ��������--------------------------------------------------------*/
/* Exported macro �궨��------------------------------------------------------------*/


/* Ĭ�ϵ�ַ */
#define GRAY_ADDR_DEF 0x4C

/**
 * @addtogroup
 * �Ҷȴ��������������ַ
*/
/**
 * @{
*/
/*PING���*/
#define GRAY_PING 0xAA
/*PING���ͨ��*/
#define GRAY_PING_OK 0x66
#define GRAY_PING_RSP GRAY_PING_OK

/* ������������ģʽ */
#define GRAY_DIGITAL_MODE 0xDD

/* ����������ȡģ������ģʽ */
#define GRAY_ANALOG_BASE 0xB0
#define GRAY_ANALOG_MODE  (GRAY_ANALOG_BASE + 0)

/* ��������һ���Ĵ���(v3.6��֮��Ĺ̼�) */
#define GRAY_ANALOG_NORMALIZE 0xCF

/* ѭ����ȡ����̽ͷģ������ n��1��ʼ��8 */
#define GRAY_ANALOG(n) (_GRAY_ANALOG_BASE_ + (n))

/* ��ɫ�ͻرȽϲ������� */
#define GRAY_CALIBRATION_BLACK 0xD0
/* ��ɫ�ͻرȽϲ������� */
#define GRAY_CALIBRATION_WHITE 0xD1

/* ��ȡ������Ϣ */
#define GRAY_ERROR 0xDE

/* �豸������� */
#define GRAY_REBOOT 0xC0

/* ��ȡ�̼��汾�� */
#define GRAY_FIRMWARE 0xC1

/* �����豸I2C��ַ */
#define GRAY_CHANGE_ADDR 0xAD

/* �㲥���õ�ַ����Ҫ�������� */
 #define GRAY_BROADCAST_RESET "\xB8\xD0\xCE\xAA\xBF\xC6\xBC\xBC"
/**
 * @}
*/

/*��������̽ͷ��ģ���ź�(CE: channel enable)*/
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
 * @brief �Ҷȴ������ṹ��
*/
typedef struct 
{
  HAL_StatusTypeDef GarySta; /*������״̬*/

  uint8_t OC[8];   /*ÿ��̽ͷ������*/

  uint8_t addr_tab[128];   /*��ʼ��ɨ���豸��ַ*/
  
  uint8_t receive_8bit;   /*8̽ͷ���ֽ�����*/

  uint8_t Ping_addr;    /*ping��ⷵ�ص�ַ*/

  uint8_t cmd; /*�û��Զ�������*/

}Gary_HandleTypeDef;

/* Exported functions prototypes ��������---------------------------------------------*/
/**
 * @brief ��I2C�õ���8λ�������źŵ����� ��ȡ��nλ������
 * @param sensor_value ����IO������
 * @param n ��1λ��1��ʼ, n=1 �Ǵ������ĵ�һ��̽ͷ����, n=8�����һ��
 * @return
 */
#define GET_NTH_BIT(sensor_value, nth_bit) (((sensor_value) >> ((nth_bit)-1)) & 0x01)


/**
 * @brief ��һ��������������е�bit
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


uint8_t Gray_Init (Gary_HandleTypeDef *GaryX); /*��������ʼ��*/

_StatusTypeDef PING_check (Gary_HandleTypeDef *GaryX);/*ping��⺯��*/

void Gary_Read_8bit (Gary_HandleTypeDef *GaryX);/*���ݶ�ȡģʽ*/

void Gary_Read_8OC (Gary_HandleTypeDef *GaryX);/*������ȡ8̽ͷ����*/


#endif /* INC_GW_GRAYSCALE_SENSOR_H_ */
