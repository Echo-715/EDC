
#include "Mymath.h"

/**
?* @brief 斜坡函数
?* @param[in] target_value 期望值
?* @param[in] current_value 当前值
?* @param[in] step_length 步长
?* @return 本次迭代结果
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
