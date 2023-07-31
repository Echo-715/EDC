

#include "Chassis_CTRL.h"

#include "Motor.h"
#include "PID.h"
/*根据灰度传感器进行判断旋转*/
void Turn_90_chack (Gary_HandleTypeDef *Gary)
{
    float output[2];

    if (Gary->OC[7] <=55)
    {
        /* code */
        while ((Gary->OC[3] >=40) || (Gary->OC[4]>=40))
        {
            /* code */
            output[0] = SpeedPID_Process(&Chassis_PID,-40,Motor.velocity[0]); 
            output[1] = SpeedPID_Process(&Chassis_PID,40,Motor.velocity[1]);
            Motor_Output(Motor_1,output);
            Motor_Output(Motor_2,output);
        }
        
    }
    else if (Gary->OC[0] <=55)
    {
        /* code */
        while ((Gary->OC[3] >=40) || (Gary->OC[4]>=40))
        {
            /* code */
            output[0] = SpeedPID_Process(&Chassis_PID,40,Motor.velocity[0]); 
            output[1] = SpeedPID_Process(&Chassis_PID,-40,Motor.velocity[1]);
            Motor_Output(Motor_1,output);
            Motor_Output(Motor_2,output);
        }
    }
    
    
}

/*通过灰度传感器进行判断*/
/*1 右转 2 左转*/
void crossroad (Gary_HandleTypeDef *Gary,uint8_t diretion)
{
    float output[2];
    if ((Gary->OC[7] <=60) && (Gary->OC[0] <= 70))
    {
        output[0] = SpeedPID_Process(&Chassis_PID,0,Motor.velocity[0]); 
        output[1] = SpeedPID_Process(&Chassis_PID,0,Motor.velocity[1]);
        Motor_Output(Motor_1,output);
        Motor_Output(Motor_2,output);
        HAL_Delay(100);
        switch (diretion)
        {
        case 1:
            /* code */
            while ((Gary->OC[3] >=40) || (Gary->OC[4]>=40))
            {
                /* code */
                output[0] = SpeedPID_Process(&Chassis_PID,-40,Motor.velocity[0]); 
                output[1] = SpeedPID_Process(&Chassis_PID,50,Motor.velocity[1]);
                Motor_Output(Motor_1,output);
                Motor_Output(Motor_2,output);
            }
            break;
        case 2:
            while ((Gary->OC[3] >=40) || (Gary->OC[4]>=40))
            {
                /* code */
                output[0] = SpeedPID_Process(&Chassis_PID,50,Motor.velocity[0]); 
                output[1] = SpeedPID_Process(&Chassis_PID,-40,Motor.velocity[1]);
                Motor_Output(Motor_1,output);
                Motor_Output(Motor_2,output);
            }
            break;
        default:
            break;
        }

        
    }

}
