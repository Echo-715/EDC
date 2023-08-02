
#include "main.h"



typedef struct 
{
    /* data */
    float Proportion_Coefficient;   //P
    float Integration_Coefficient;   //I
    float Differentiation_Coefficient; //D
    float LastError;
    
    float Eorror_MaxOutPut;
    float Integration_MaxOutPut;
    float Differentiation_MaxOutPut;
    float PID_FailMaxOutPut;
			
}PID_parameter_Typedef;


extern PID_parameter_Typedef Yaw_SpeedPID;
extern PID_parameter_Typedef Yaw_LocationPID;
extern PID_parameter_Typedef Pitch_SpeedPID;
extern PID_parameter_Typedef Pitch_LocationPID;

void PID_Init (PID_parameter_Typedef *PID,float Kp,float Ki,float Kd,float PIDmax,float Imax,float Dmax);
int SpeedPID_Process (PID_parameter_Typedef *PID,int Expecat_Value, int Actual_Value );
int LocationPID_Process (PID_parameter_Typedef *PID,int Expecat_Value, int Actual_Value );
float PID_LimitMax(float Input,float Max);

