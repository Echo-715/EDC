

#ifndef __Gimbal_H__
#define __Gimbal_H__

#include "main.h"
#include "Motor.h"
#include "PID.h"

#define Yaw_motorID   0 /*对应电调ID1*/
#define Pitch_motorID  1  /*对应电调ID2*/
#define INITIAL_POSITION   0

typedef struct 
{
    /* data */
    float Position;
    int16_t Output;
    
}GimbalTypeDef;

extern GimbalTypeDef Yaw;

extern GimbalTypeDef Pitch;

void Gimbal_StrPID(GimbalTypeDef *gimbal, MotorTypeDef *M3508,
                    PID_parameter_Typedef *speed,
                    PID_parameter_Typedef*location, 
                    int ExpLocation,uint8_t id);

void Gimbal_CTRL(void);
void MOD2 (void);
void MOD3 (void);

#endif
