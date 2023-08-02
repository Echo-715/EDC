///@brief 求绝对值
#define abs(x) ((x)>0?(x):-(x))

/**
?* @addtogroup 关系运算符
?* @{
?*/
/// @brief 求两者间最小值
#define min(x,y)  ((x)>(y)?(y):(x))
/// @brief 求两者间最大值
#define max(x,y)  ((x)>(y)?(x):(y))
/// @brief 限幅函数
#define constrain(amt,high,low) ((amt)>(low)?min((amt),(high)):(low))
/// @brief 求符号
#define sign(x) ((x) > 0 ? (+1) : ((x) < 0 ? (-1) : 0))


float Ramp_float(float target_value,float current_value,float step_length);
