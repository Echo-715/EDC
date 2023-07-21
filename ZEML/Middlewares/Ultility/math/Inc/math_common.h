/**
 ******************************************************************************
 * @file    math_common.h
 * @author  SY7_yellow
 * @brief   通用数学运算库
 * @version v0.1-alpha
 * @date    2023-7-6
 ******************************************************************************
 * @note
 * 
 * 误差小于0.01%不标注误差情况。\n
 * 在运算出现错误时候默认返回0,并且置math_errno为对应错误标志位。
 * 
 ******************************************************************************
 * @attention
 * 
 * 文件编码：UTF-8，出现乱码请勿上传！
 * File encoding:UTF-8，Do not upload garbled code!\n
 * 数学运算库的代码更新前请进行多次测试，没有问题后才更新至此。\n
 * 实现时候使用通用方法实现后再调用arm_math.h中的函数实现。\n
 * 优先兼容arm_math.h的格式，使用第三方的库的时候注意检查。\n
 * 浮点类型固定为float,如果需要使用double请调用"math.h"或使用其他第三方库。
 * (Cortex-M系列的fpu只有硬件单精度计算，双精度的依然是软件计算)\n
 * 修改后测试没问题记得修改版本号，未经过测试的请使用加上后缀alpha,beta...并且请
 * 勿合并到master。\n
 * 防御性编程，对输入参数做有效性检查，并返回错误号。
 * 非必要不要包含太多头文件
 * 
 ******************************************************************************
 * @par 修改日志
 * <table>
 * <tr><th>Date         <th>Version     <th>Author      <th>Description
 * <tr><td>2023-7-6     <td>0.1-alpha   <td>SY7_yellow  <td>创建初始版本
 * <tr><td>2023-7-8     <td>0.1-beta    <td>SY7_yellow  <td>用标准库替代比标准库慢的函数
 * </table>
 * @note 此修改日志主要是增减函数的日志,后面说明说明清楚增减了哪些函数，修改bug
 * 之类的无需在此说明(git上可以看得到)。
 ******************************************************************************
 */
#ifndef _MATH_COMMON_H_
#define _MATH_COMMON_H_
#include "math.h"
#include "arm_math.h"
/**
 * @addtogroup 数学库
 * @{
 */
///@brief 启用输入参数有效性检查
//#define USE_MATH_ASSERT

///@brief 常数定义
#define PI 3.1415926535f
#define e 2.7182818284f
#define ln_2 0.6931471828f
#define ln_10 2.3025850929f

///@brief 计算精度
#define eps2 0.0000001f
#define eps1 eps2 *eps2

///@brief 检查输入参数是否为NaN
#define IS_NAN(x)           (!isnan(x))
///@brief 检查输入参数是否为INF
#define IS_INF(x)           (!isinf(x))
///@brief 检查输入参数是否为NaN和Inf
#define IS_NAN_INF(x)       (!isnan(x) || !isinf(x))
///@brief 检查输入参数是否为空指针
#define IS_NULL_POINT(x)    (x != (void*)0)
///@brief 数学库断言函数
#ifdef USE_MATH_ASSERT
#define math_assert_param(expr) if(!expr){\
                            math_errno = MATH_PARAMETERS_ERROR;\
                            return 0;\
                            }
#else
#define math_assert_param(expr) ((void)0U)
#endif

/// @brief 数学运算库整型定义
typedef int32_t integer_t;
/// @brief 数学运算库错误码结构体

typedef enum
{
    MATH_SUCCESS = 0,       /**< 无错误*/
    MATH_PARAMETERS_ERROR,  /**< 参数错误*/
    MATH_NANINF,            /**< 产生NaN或者InF错误*/
    MATRIX_ERROR,           /**< 矩阵错误*/
} math_errno_t;
/// @brief 数学运算库错误码
extern math_errno_t math_errno;

///@brief 求绝对值
#define abs(x)    ((x)>0?(x):-(x))

/**
 * @addtogroup 关系运算符
 * @{
 */
///@brief 求两者间最小值
#define min(x,y)  ((x)>(y)?(y):(x))
///@brief 求两者间最大值
#define max(x,y)  ((x)>(y)?(x):(y))
/// @brief 限幅函数
#define constrain(amt,high,low) ((amt)>(low)?min((amt),(high)):(low))

/// @brief 斜坡函数
/// @param target_value 期望值
/// @param current_value 当前值
/// @param step_length 步长
/// @return 本次迭代结果
float Ramp_float(float target_value,float current_value,float step_length);
/**
 * @} 关系运算符结尾
 */

/**
 * @addtogroup 常规数学函数
 * 该组函数为常用数学函数，其精度通常较高，运算量大，适合常规精度应用。
 * @{
 */

/// @brief 快速幂
/// @param[in] a 底数
/// @param[in] n 指数(必须为整型)
/// @return a^n的结果
float math_pow(float a, integer_t n);

/// @brief 浮点取模函数
/// @param x 被除数
/// @param y 模值
/// @return x mod y结果
float math_fmod(float x, float y);
/**
 * @addtogroup 指数对数函数
 * @{
 */
/// @brief 求exp
/// @param[in] x 输入值
/// @return e^x的结果
float math_exp(float x);

/// @brief 实数幂函数
/// @param[in] a 底数
/// @param[in] n 指数
/// @return a^n的结果
float math_powf(float a, float n);

/// @brief 求自然对数
/// @param[in] x 输入值
/// @return lnx结果
float math_ln(float x);

/// @brief 求对数
/// @param[in] a 真数
/// @param[in] x 底数
/// @return log_a(x)结果
float math_log(float a,float x);

/**
 * @} 指数对数函数末尾
 */

/// @brief 求平方根倒数
/// @param[in] x 输入值
/// @return 1/sqrt(x)结果
float math_invsqrt(float x);

/// @brief 求平方根
/// @param[in] x 输入值
/// @return sqrt(x)结果
float math_sqrt(float x);

/**
 * @addtogroup 三角函数
 * @{
 */
/// @brief 求sinx和cosx
/// @param[in] x 输入值(弧度)
/// @param[out] sinx sinx结果
/// @param[out] cosx cosx结果
void math_sin_cos(float x,float *sinx,float *cosx);

/// @brief 求正弦函数
/// @param[in] x 输入值(弧度)
/// @return sinx的结果
float math_sin(float x); 

/// @brief 求余弦函数
/// @param[in] x 输入值(弧度)
/// @return cosx的结果
float math_cos(float x);

/// @brief 求正切函数
/// @param[in] x 输入值
/// @return tanx的结果
float math_tan(float x);

/**
 * @} 三角函数末尾
 */

/// @brief 求阶乘
/// @param[in] x 输入值
/// @return x!
float math_factorial(integer_t x);

/**
 * @addtogroup 双曲函数
 * @{
 */
/// @brief 求双曲正弦
/// @param[in] x 输入值
/// @return sinhx的结果
float math_sinh(float x);

/// @brief 求双曲余弦
/// @param[in] x 输入值
/// @return coshx的结果
float math_cosh(float x);

/// @brief 求双曲正切
/// @param[in] x 输入值
/// @return tanhx的结果
float math_tanh(float x);

/**
 * @} 双曲函数末尾
 */


/**
 * @} 常规数学函数末尾
*/

/**
 * @addtogroup 位运算函数
 * 该组函数为位数学函数，提供更多拓展的位运算。
 * @{
 */

/// @brief 求二进制数x的最高位
/// @param[in] x 输入值
/// @param[out] y x最高位所在位数
/// @return x保留最高位结果
integer_t high_bit(integer_t x, integer_t *y);

/// @brief 求二进制数x的最低位
/// @param[in] x 输入值
/// @param[out] y x最低位所在位数
/// @return x保留最低位结果
integer_t low_bit(integer_t x, integer_t *y);
/**
 * @} 位运算函数末尾
*/
/**
 * @} 数学库末尾
*/
#endif