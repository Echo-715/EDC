
#include "Motor.h"
MotorTypeDef M3508;

void MotorData_Process ( MotorTypeDef*M3508, uint8_t can_rx_data_buf[][8])
{
		// 
	for (uint8_t i = 0; i < 8; i++)
	{
		/* code */
		//转子角度
		M3508->ID[i].Rotor_angle = (can_rx_data_buf[i][0]<<8) | can_rx_data_buf[i][1];
		//电机转速
		M3508->ID[i].Rotor_speed = (can_rx_data_buf[i][2]<<8) | can_rx_data_buf[i][3];
		//转矩电流
		M3508->ID[i].Torque_current = (can_rx_data_buf[i][4]<<8) | can_rx_data_buf[i][5];
	}

}

