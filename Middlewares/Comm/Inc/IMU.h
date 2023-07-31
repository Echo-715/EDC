
#ifndef __IMU_H__
#define __IMU_H__

#include "stm32f1xx_hal.h"

typedef struct 
{
    /* data */
    int16_t Accel[3]; /* 0ÊÇYaw 1ÊÇRoll 2ÊÇPitch*/
    int16_t Gyrop[3];
    int16_t Temperature;

}IMUTypeDef;

extern IMUTypeDef BMI088;

void IMU_MesReceive ( CAN_RxHeaderTypeDef *RxMessage,uint8_t CAN_Data[8], IMUTypeDef *IMU);

#endif

