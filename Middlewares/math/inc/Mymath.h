///@brief �����ֵ
#define abs(x) ((x)>0?(x):-(x))

/**
?* @addtogroup ��ϵ�����
?* @{
?*/
/// @brief �����߼���Сֵ
#define min(x,y)  ((x)>(y)?(y):(x))
/// @brief �����߼����ֵ
#define max(x,y)  ((x)>(y)?(x):(y))
/// @brief �޷�����
#define constrain(amt,high,low) ((amt)>(low)?min((amt),(high)):(low))
/// @brief �����
#define sign(x) ((x) > 0 ? (+1) : ((x) < 0 ? (-1) : 0))


float Ramp_float(float target_value,float current_value,float step_length);
