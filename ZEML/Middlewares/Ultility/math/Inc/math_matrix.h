/**
 ******************************************************************************
 * @file    math_matrix.h
 * @author  Marc Pony
 * @brief   矩阵运算库
 * @version v1.0-alpha
 * @date 2023-7-6
 * @see https://blog.csdn.net/maple_2014/article/details/119720296
 ******************************************************************************
 * @note
 *    
 *
 ******************************************************************************
 * @attention
 * 
 * 文件编码：UTF-8，出现乱码请勿上传！
 * File encoding:UTF-8,Do not upload garbled code!\n
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
 * <tr><td>2023-7-6     <td>0.1-alpha   <td>SY7_yellow  <td>初始arm_math.h矩阵运算的支持
 * </table>
 * @note 此修改日志主要是增减函数的日志,后面说明说明清楚增减了哪些函数，修改bug
 * 之类的无需在此说明(git上可以看得到)。
 ******************************************************************************
 */
#ifndef _MATH_MATRIX_H_
#define _MATH_MATRIX_H_
#include "math_common.h"

/**
 * @brief 矩阵结构体定义
 * @details 该结构指定矩阵的大小，然后指向数据数组。数组的大小和值按行顺序排列。
 * 也就是，矩阵元素 （i， j） 存储在：numRows * numCols： pData[i*numCols + j]
 */
#ifdef _ARM_MATH_H
typedef arm_matrix_instance_f32 matrix_t;
#else
typedef struct
{
   uint16_t numRows;     /**< 矩阵行个数     */
   uint16_t numCols;     /**< 矩阵列个数     */
   float *pData; /**< 矩阵数据指针   */
} matrix_t;
#endif
///@brief 矩阵库断言函数
#ifdef USE_MATH_ASSERT
#define matirx_assert_param(expr)         \
   if (!expr)                             \
   {                                      \
      math_errno = MATH_PARAMETERS_ERROR; \
      return INPUT_PARAMETERS_ERROR;      \
   }
#else
#define matirx_assert_param(expr)        ((void)0U)
#endif
/**
 * @brief 矩阵运算状态枚举结构体
 * @details 该结构体作为矩阵返回值输出，说明矩阵运算状态。
 * 返回值非0且不为1时候会置math_errno为MATRIX_ERROR。
 * 返回值为1时候会置math_errno为MATH_PARAMETERS_ERROR。
 */
typedef enum
{
   MATRIX_NO_ERROR = 0,                          /**< 无错误                                  */
   INPUT_PARAMETERS_ERROR,                       /**< 输入参数错误                            */
   MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL,             /**< 矩阵行列不相等                          */
   MATRIX_MULTIPLICATION_ERROR,                  /**< 矩阵乘法错误(左矩阵列不等于右矩阵行)    */
   MATRIX_MUST_BE_SQUARE,                        /**< 矩阵必须为方阵                          */
   MATRIX_EQUATION_HAS_NO_SOLUTIONS,             /**< 矩阵方程无解                            */
   MATRIX_EQUATION_HAS_INFINITY_MANNY_SOLUTIONS, /**< 矩阵方程有无穷多解                      */
   CREATE_MATRIX_FAILED,                         /**< 创建矩阵失败                            */
   MATRIX_TRANSPOSE_FAILED                       /**< 矩阵转置失败                            */

} matrix_error_t;

/**
 * @addtogroup 数学库
 * @{
 */
/**
 * @addtogroup 矩阵运算函数
 * 常用的矩阵运算
 * @{
 */
/// @brief 矩阵初始化
/// @param[out] pMat 矩阵结构体指针
/// @param[in] row 行个数
/// @param[in] column 列个数
/// @param[in] pData 数据指针
/// @return 矩阵运算状态
matrix_error_t matrix_init(matrix_t *pMat,const uint16_t row,const uint16_t column,float *pData);

/// @brief 矩阵加法，计算A+B=C
/// @param[in] pMatA 输入矩阵A
/// @param[in] pMatB 输入矩阵B
/// @param[out] pMatC 输出矩阵C
/// @return 矩阵运算状态
matrix_error_t matrix_add(const matrix_t *pMatA, const matrix_t *pMatB, matrix_t *pMatC);

/// @brief 矩阵减法，计算A-B=C
/// @param[in] pMatA 输入矩阵A
/// @param[in] pMatB 输入矩阵B
/// @param[out] pMatC 输出矩阵C
/// @return 矩阵运算状态
matrix_error_t matrix_sub(const matrix_t *pMatA, const matrix_t *pMatB, matrix_t *pMatC);

/// @brief 矩阵乘法，计算A*B=C
/// @param[in] pMatA 输入矩阵A
/// @param[in] pMatB 输入矩阵B
/// @param[out] pMatC 输出矩阵C
/// @return 矩阵运算状态
matrix_error_t matrix_mult(const matrix_t *pMatA, const matrix_t *pMatB, matrix_t *pMatC);

/// @brief 矩阵的逆，计算A^-1=B
/// @param[in] pMatA 输入矩阵A
/// @param[out] pMatB 输出矩阵B
/// @return 矩阵运算状态
matrix_error_t matrix_inverse(const matrix_t *pMatA, matrix_t *pMatB);

/// @brief 矩阵的转置，计算A^T=B
/// @param[in] pMatA 输入矩阵A
/// @param[out] pMatB 输出矩阵B
/// @return 矩阵运算状态
matrix_error_t matrix_trans(const matrix_t *pMatA,matrix_t *pMatB);

/// @brief 矩阵的缩放，计算kA=B
/// @param[in] k 缩放系数
/// @param[in] pMatA 输入矩阵A
/// @param[out] pMatB 输出矩阵B
/// @return 矩阵运算状态
matrix_error_t matrix_scale(const float k,const matrix_t *pMatA,matrix_t *pMatB);

/// @brief 矩阵的行列式，计算|A|=y
/// @param[in] pMatA 输入矩阵A
/// @param[out] y 行列式结果
/// @return 矩阵运算状态
matrix_error_t matrix_determinant(const matrix_t *pMatA, float *y);
/**
 * @} 矩阵运算函数末尾
 */
/**
 * @} 数学库末尾
 */

#endif