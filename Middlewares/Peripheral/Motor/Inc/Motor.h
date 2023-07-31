#ifndef __Motor_H__
#define __Motor_H__

#include "main.h"

typedef struct 
{
    /* data */
    struct 
    {
        /* data */
        int16_t Rotor_angle;
        int16_t Rotor_speed;
        int16_t Torque_current;
        int16_t Temperature;

    }ID[8];
    
}MotorTypeDef;

extern MotorTypeDef M3508;
void MotorData_Process ( MotorTypeDef*M3508, uint8_t can_rx_data_buf[][8]);


#endif
