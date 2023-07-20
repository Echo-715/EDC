/**
  ******************************************************************************
  * @file   Buzzer.c
  * @brief  提供蜂鸣器使用的各种声调API声明，一些操作宏定义
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* includes --------------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
/* Private includes 非官方头文件声明----------------------------------------------------------*/
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
#define  proport          72000 	//Tclk/(arr+1)=72000000/(1000)
 /*根据Tout= ((arr+1)*(psc+1))/Tclk推出psc值就是本句define定义的值，Tout为音调频率131Hz的倒数，Tclk=72MHz */                                                
#define  L_do        ((proport/262)-1)/*低调　do 的频率*/
#define  L_re        ((proport/296)-1)/*低调　re 的频率*/
#define  L_mi        ((proport/330)-1)/*低调　mi 的频率*/
#define  L_fa        ((proport/349)-1)/*低调　fa 的频率*/
#define  L_sol       ((proport/392)-1)/*低调　sol 的频率*/
#define  L_la        ((proport/440)-1)/*低调　la 的频率*/
#define  L_si        ((proport/494)-1)/*低调　si 的频率*/

#define  M_do        ((proport/523)-1)/*中调　do 的频率*/
#define  M_re        ((proport/587)-1)/*中调　re 的频率*/
#define  M_mi        ((proport/659)-1)/*中调　mi 的频率*/
#define  M_fa        ((proport/699)-1)/*中调　fa 的频率*/
#define  M_sol       ((proport/784)-1)/*中调　so 的频率*/
#define  M_la        ((proport/880)-1)/*中调　la 的频率*/
#define  M_si        ((proport/988)-1)/*中调　si 的频率*/
 
#define  H_do        ((proport/1048)-1)/*高调　do 的频率*/
#define  H_re        ((proport/1176)-1)/*高调　re 的频率*/
#define  H_mi        ((proport/1320)-1)/*高调　mi 的频率*/
#define  H_fa        ((proport/1480)-1)/*高调　fa 的频率*/
#define  H_sol       ((proport/1640)-1)/*高调　so 的频率*/
#define  H_la        ((proport/1760)-1)/*高调　la 的频率*/
#define  H_si        ((proport/1976)-1)/*高调　si 的频率*/
 
#define  Z0       0

/* Exported functions prototypes 函数声明---------------------------------------------*/
/**
 * @addtogroup 蜂鸣器基本操作API
 * @{
*/
void Buzzer_Volume (int16_t Pluse);/*改变蜂鸣器音量*/
void Buzzer_Tonal (int16_t PSC);/*改变蜂鸣器音调*/
void Buzzer_OFF (void);/*关闭蜂鸣器*/
 /**
  * @ }
 */

/**
 * @addtogroup 
 * @{
*/
void Boot_Prompt (void);/*开机提示音*/
 /**
  * @ }
 */

