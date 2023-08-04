

#ifndef __Gimbal_H__
#define __Gimbal_H__

#include "main.h"
#include "Motor.h"
#include "PID.h"

#define Yaw_motorID   0 /*对应电调ID1*/
#define Pitch_motorID  1  /*对应电调ID2*/
#define INITIAL_POSITION   0

#define Inital_Pitch    3275
#define Inital_Yaw      3270
#define MOVE_SPEED      0.2f
#define Yaw_K       1.9 //1.4
#define Pitch_k     1.07//1.04
#define Origin_x    2950
#define Origin_y    3495
//绕圈时，pitch和yaw的移动数值

#define Poin1_Yaw (Inital_Yaw+330)
#define Poin1_Pitch (Inital_Pitch-310)

#define Poin2_Yaw (Inital_Yaw-320) //2875 -- -250

#define Poin3_Pitch (Inital_Pitch+230) //3510 -- 250

#define Poin4_Yaw (Inital_Yaw+330)

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
void MOD4(void);

#endif
