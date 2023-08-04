
#include "Gimbal.h"
#include "can.h"
#include "Key.h"
#include "Mymath.h"
#include "usart.h"


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
        
        Yaw.Position = Inital_Yaw;
        Pitch.Position = Inital_Pitch;
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
    else if ((Allkey.key1.Flag == 4)&&(Allkey.key2.Flag ==1))
    {
        /* code */
        MOD4();
    }
    
    else if (initcompaly)
    {
        /* code */
        Yaw.Position = Inital_Yaw;
        Pitch.Position = Inital_Pitch;

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
        Yaw.Position = Inital_Yaw;
        Pitch.Position = Inital_Pitch;
        flag[2]++;
    }

    if ((flag[0]==0)&&(flag[1]==0))
    {
        /* code */
        Yaw.Position = Ramp_float(Poin1_Yaw,Yaw.Position,MOVE_SPEED);//
        if (Yaw.Position == Poin1_Yaw)
        {
            /* code */
            flag[0]=1;
            flag[1]=1;
        }
        
    }
    if ((flag[0]==1)&&(flag[1]==1))
    {
        /* code */
        Pitch.Position = Ramp_float(Poin1_Pitch,Pitch.Position,MOVE_SPEED);//3167.44
        if (Pitch.Position == Poin1_Pitch)
        {
            /* code */
            flag[0]=2;
            flag[1]=2;
        }
    }
    if ((flag[0]==2)&&(flag[1]==2))
    {
        /* code */
        Yaw.Position = Ramp_float(Poin2_Yaw,Yaw.Position,MOVE_SPEED);//2860
        if (Yaw.Position == Poin2_Yaw)
        {
            /* code */
            flag[0]=3;
            flag[1]=3;
        }
        
    }
    if ((flag[0]==3)&&(flag[1]==3))
    {
        /* code */
        Pitch.Position = Ramp_float(Poin3_Pitch,Pitch.Position,MOVE_SPEED);//3598
        if(Pitch.Position == Poin3_Pitch)
        {
            flag[0]=4;
            flag[1]=4;
        }

    }
    if ((flag[0]==4)&&(flag[1]==4))
    {
        Yaw.Position = Ramp_float(Poin4_Yaw,Yaw.Position,MOVE_SPEED);
        if (Yaw.Position == Poin4_Yaw)
        {
            /* code */
            flag[0] =5;
            flag[1] =5;
        }
        
    }
    if((flag[0]==5)&&(flag[1]==5))
    {
        Pitch.Position = Ramp_float(Inital_Pitch,Pitch.Position,MOVE_SPEED);

        if (Pitch.Position == Inital_Pitch)
        {
            flag[0]=6;
            flag[1]=6;
        }
        
    }
    if ((flag[0]==6)&&(flag[1]==6))
    {
        /* code */
        Yaw.Position = Ramp_float(Inital_Yaw,Yaw.Position,MOVE_SPEED);

    }
    

    Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
    Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);

}

void MOD3 (void)
{
    if ((flag[2] ==0))
    {
        /* code */
        Yaw.Position = Ramp_float((Inital_Yaw-320),Yaw.Position,0.6f);
        Pitch.Position = Ramp_float((Inital_Pitch+200),Pitch.Position,1.0f);
        if ((Yaw.Position == (Inital_Yaw-320))&&(Pitch.Position == (Inital_Pitch+200)))
        {
            /* code */
            flag[2] =1;
        }
        
    }
    if (flag[2]==1)
    {
        /* code */
        Yaw.Position = Ramp_float((Inital_Yaw+90),Yaw.Position,0.1f);
       if (Yaw.Position == (Inital_Yaw+90))
       {
        /* code */
        flag[2]=2;

       }
        
    }
    if (flag[2]==2)
    {
        /* code */
        Pitch.Position = Ramp_float((Inital_Pitch+90),Pitch.Position,0.1f);
        if (Pitch.Position == (Inital_Pitch+90))
        {
            /* code */
            flag[2]=3;
        }
        
    }
    if (flag[2]==3)
    {
        /* code */
        Yaw.Position = Ramp_float((Inital_Yaw-320),Pitch.Position,0.1f);
    }
    
    
    
    

    Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
    Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);

}

void MOD4(void)
{
    if (flag[3] == 0)
    {

        Yaw.Position = Ramp_float(Inital_Yaw-320,Yaw.Position,0.1f);
        Pitch.Position = Ramp_float (Inital_Pitch+230,Pitch.Position,0.1f);
        if ((Yaw.Position == Inital_Yaw-320)&&(Pitch.Position == Inital_Pitch+230))
        {
            /* code */
            flag[3] =1;
        }  

    }
    
    /* code */
    if (flag[3]==1)
    {
        /* code */
        Yaw.Position = Ramp_float(Origin_x+(Yaw_K*(frame.Num[0].X)),Yaw.Position,0.1f);
        Pitch.Position = Ramp_float (Origin_y-(Pitch_k*(frame.Num[0].Y)),Pitch.Position,0.1f);
        if ((Yaw.Position == Origin_x-(Yaw_K*(frame.Num[0].X)))&&(Pitch.Position == Origin_y-(Pitch_k*(frame.Num[0].Y))))
        {
            /* code */
            flag[3] =2;
        }  
    }

    Gimbal_StrPID(&Yaw,&M3508,&Yaw_SpeedPID,&Yaw_LocationPID,Yaw.Position,Yaw_motorID);
    Gimbal_StrPID(&Pitch,&M3508,&Pitch_SpeedPID,&Pitch_LocationPID,Pitch.Position,Pitch_motorID);

}
