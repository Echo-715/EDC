
#include "Mymath.h"

/**
?* @brief б�º���
?* @param[in] target_value ����ֵ
?* @param[in] current_value ��ǰֵ
?* @param[in] step_length ����
?* @return ���ε������
?*/
float Ramp_float(float target_value,float current_value,float step_length)
{
 float s = sign(target_value - current_value);
 float temp = current_value + s * step_length;
 if(s*(temp - target_value)>=0)
 {
    return target_value;
 }
 else
 {
    return temp;
 }
}
