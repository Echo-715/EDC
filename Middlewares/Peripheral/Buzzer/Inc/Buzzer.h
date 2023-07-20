/**
  ******************************************************************************
  * @file   Buzzer.c
  * @brief  �ṩ������ʹ�õĸ�������API������һЩ�����궨��
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* includes --------------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
/* Exported types ���Ͷ���------------------------------------------------------------*/
/* Exported constants ��������--------------------------------------------------------*/
/* Exported macro �궨��------------------------------------------------------------*/
#define  proport          72000 	//Tclk/(arr+1)=72000000/(1000)
 /*����Tout= ((arr+1)*(psc+1))/Tclk�Ƴ�pscֵ���Ǳ���define�����ֵ��ToutΪ����Ƶ��131Hz�ĵ�����Tclk=72MHz */                                                
#define  L_do        ((proport/262)-1)/*�͵���do ��Ƶ��*/
#define  L_re        ((proport/296)-1)/*�͵���re ��Ƶ��*/
#define  L_mi        ((proport/330)-1)/*�͵���mi ��Ƶ��*/
#define  L_fa        ((proport/349)-1)/*�͵���fa ��Ƶ��*/
#define  L_sol       ((proport/392)-1)/*�͵���sol ��Ƶ��*/
#define  L_la        ((proport/440)-1)/*�͵���la ��Ƶ��*/
#define  L_si        ((proport/494)-1)/*�͵���si ��Ƶ��*/

#define  M_do        ((proport/523)-1)/*�е���do ��Ƶ��*/
#define  M_re        ((proport/587)-1)/*�е���re ��Ƶ��*/
#define  M_mi        ((proport/659)-1)/*�е���mi ��Ƶ��*/
#define  M_fa        ((proport/699)-1)/*�е���fa ��Ƶ��*/
#define  M_sol       ((proport/784)-1)/*�е���so ��Ƶ��*/
#define  M_la        ((proport/880)-1)/*�е���la ��Ƶ��*/
#define  M_si        ((proport/988)-1)/*�е���si ��Ƶ��*/
 
#define  H_do        ((proport/1048)-1)/*�ߵ���do ��Ƶ��*/
#define  H_re        ((proport/1176)-1)/*�ߵ���re ��Ƶ��*/
#define  H_mi        ((proport/1320)-1)/*�ߵ���mi ��Ƶ��*/
#define  H_fa        ((proport/1480)-1)/*�ߵ���fa ��Ƶ��*/
#define  H_sol       ((proport/1640)-1)/*�ߵ���so ��Ƶ��*/
#define  H_la        ((proport/1760)-1)/*�ߵ���la ��Ƶ��*/
#define  H_si        ((proport/1976)-1)/*�ߵ���si ��Ƶ��*/
 
#define  Z0       0

/* Exported functions prototypes ��������---------------------------------------------*/
/**
 * @addtogroup ��������������API
 * @{
*/
void Buzzer_Volume (int16_t Pluse);/*�ı����������*/
void Buzzer_Tonal (int16_t PSC);/*�ı����������*/
void Buzzer_OFF (void);/*�رշ�����*/
 /**
  * @ }
 */

/**
 * @addtogroup 
 * @{
*/
void Boot_Prompt (void);/*������ʾ��*/
 /**
  * @ }
 */

