
#include "Gimbal.h"
#include "can.h"
#include "Key.h"

GimbalTypeDef Yaw;
GimbalTypeDef Pitch;

/*串级PID控制*/
void Gimbal_StrPID(GimbalTypeDef *gimbal, MotorTypeDef *M3508,
                    PID_parameter_Typedef *speed,
                    PID_parameter_Typedef*location, 
                    int ExpLocation,uint8_t id)
{
    gimbal->Output = SpeedPID_Process(speed,
                                    LocationPID_Process(location,ExpLocation,M3508->ID[id].Rotor_angle),
                                    M3508->ID[id].Rotor_speed);
}



void Gimbal_CTRL(void)
{
    if((Allkey.key1.Flag==1)&&(Allkey.key2.Flag==1))
    {  
        Yaw.Position = 3230;
        Pitch.Position = 3244;
    Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
    Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);
    }
    else
    {
        Yaw.Output=0;
        Pitch.Output =0;
    }
    /*输出处理*/
	

    /*输出发送*/
    CAN_Send_Message(0X200,Yaw.Output,Pitch.Output,0,0);

}
