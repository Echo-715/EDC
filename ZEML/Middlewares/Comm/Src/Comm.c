#include "Comm.h"
#include "can.h"

IMUTypeDef BMI088;

void IMU_MesReceive ( CAN_RxHeaderTypeDef *RxMessage,uint8_t CAN_Data[8], IMUTypeDef *IMU)
{
 
	switch (RxMessage->StdId)
	{
		case 0x020://接收加速度报文
		
			IMU->Accel[0] = (int16_t)((CAN_Data[0]<<8) | CAN_Data[1]);
			IMU->Accel[1] = (int16_t)((CAN_Data[2]<<8) | CAN_Data[3]);
			IMU->Accel[2] = (int16_t)((CAN_Data[4]<<8) | CAN_Data[5]);
		break;
		
		case 0x021://接收角速度报文

			IMU->Gyrop[0] = (int16_t)((CAN_Data[0]<<8) | CAN_Data[1]);
			IMU->Gyrop[1] = (int16_t)((CAN_Data[2]<<8) | CAN_Data[3]);
			IMU->Gyrop[2] = (int16_t)((CAN_Data[4]<<8) | CAN_Data[5]);
		break;
	default:
		  break;
	}

}
