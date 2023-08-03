
#include "Gimbal.h"
#include "can.h"
#include "Key.h"
#include "Mymath.h"


GimbalTypeDef Yaw;
GimbalTypeDef Pitch;
uint8_t flag[10];
uint8_t initcompaly;

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
        for (uint8_t i = 0; i < 10; i++)
        {
            /* code */
            flag[i] =0;
        }
        
        Yaw.Position = 3230;
        Pitch.Position = 3230;
        initcompaly = 1; 
        Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
        Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);
    }
    else if ((Allkey.key1.Flag==2)&&(Allkey.key2.Flag==1))
    {
        /* code */
        MOD2();
    }
    else if ((Allkey.key1.Flag==3)&&(Allkey.key2.Flag==1))
    {
        /* code */
        MOD3();
    }
    else if (initcompaly)
    {
        /* code */
        Yaw.Position = 3230;
        Pitch.Position = 3230;

        Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
        Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);

    }
    
    /*输出发送*/
    CAN_Send_Message(0X200,Yaw.Output,Pitch.Output,0,0);

}
 

void MOD2 (void)
{
    if (flag[2]==0)
    {
        /* code */
        Yaw.Position = 3230;
        Pitch.Position = 3244;
        flag[2]++;
    }

    if ((flag[0]==0)&&(flag[1]==0))
    {
        /* code */
        Yaw.Position = Ramp_float(3600,Yaw.Position,0.3f);//
        if (Yaw.Position == 3600)
        {
            /* code */
            flag[0]=1;
            flag[1]=1;
        }
        
    }
    if ((flag[0]==1)&&(flag[1]==1))
    {
        /* code */
        Pitch.Position = Ramp_float(2890,Pitch.Position,0.3f);//3167.44
        if (Pitch.Position == 2890)
        {
            /* code */
            flag[0]=2;
            flag[1]=2;
        }
    }
    if ((flag[0]==2)&&(flag[1]==2))
    {
        /* code */
        Yaw.Position = Ramp_float(2845,Yaw.Position,0.3f);//2860
        if (Yaw.Position == 2845)
        {
            /* code */
            flag[0]=3;
            flag[1]=3;
        }
        
    }
    if ((flag[0]==3)&&(flag[1]==3))
    {
        /* code */
        Pitch.Position = Ramp_float(3540,Pitch.Position,0.3f);//3598
        if(Pitch.Position == 3540)
        {
            flag[0]=4;
            flag[1]=4;
        }

    }
    if ((flag[0]==4)&&(flag[1]==4))
    {
        Yaw.Position = Ramp_float(3600,Yaw.Position,0.3f);
        if (Yaw.Position == 3600)
        {
            /* code */
            flag[0] =5;
            flag[1] =5;
        }
        
    }
    if((flag[0]==5)&&(flag[1]==5))
    {
        Pitch.Position = Ramp_float(3244,Pitch.Position,0.3f);

        if (Pitch.Position == 3244)
        {
            flag[0]=6;
            flag[1]=6;
        }
        
    }
    if ((flag[0]==6)&&(flag[1]==6))
    {
        /* code */
        Yaw.Position = Ramp_float(3230,Yaw.Position,0.3f);

    }
    

    Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
    Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);

}

void MOD3 (void)
{
    if (flag[3] == 0)
    {
        /* code */
        Yaw.Position = 3230;
        Pitch.Position = 3244;

        flag[3]++;
    }
    
    Yaw.Position = Ramp_float(3600,Yaw.Position,0.3f);
    Pitch.Position = Ramp_float(3600,Pitch.Position,0.25f);

    Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
    Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);

}

