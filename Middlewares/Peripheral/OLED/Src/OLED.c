/**
  ******************************************************************************
  * @file   OLED.c
  * @brief  提供OLED使用的初始化，基本设置，以及各种应用封装
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* Private includes 非官方头文件声明----------------------------------------------------------*/
#include "OLED.h"
#include "asc.h"
/* Exported types 类型定义------------------------------------------------------------*/
/* Exported constants 常量定义--------------------------------------------------------*/
/* Exported macro 宏定义------------------------------------------------------------*/
/* Exported functions prototypes 函数声明---------------------------------------------*/
/**
 * @addtogroup OLED初始化及基本操作API
 * @{
*/
/**
  * @brief  OLED命令写入函数
  * @param  IIC_Command 写入的指令
  * @retval None
  */
void OLED_ComWrite(uint8_t IIC_Command) 
{
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,COMM,I2C_MEMADD_SIZE_8BIT,&IIC_Command,1,100);
}

/**
  * @brief  OLED数据写入函数
  * @param  IIC_Data：写入的数据
  * @note   数据大小为一个字节
  * @retval None
  */
void OLED_DataWrite(uint8_t IIC_Data) 
{
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,DATA,I2C_MEMADD_SIZE_8BIT,&IIC_Data,1,100);
}

/**
  * @brief  OLED初始化函数
  * @param  None
  * @retval None
  */
void OLED_Init(void)
{
	HAL_Delay(100); //这里的延时很重要
	
	OLED_ComWrite(0xAE); /*display off 显示关闭*/
	OLED_ComWrite(0x20); /*Set Memory Addressing Mode 设置内存寻址模式*/
	OLED_ComWrite(0x10); /*00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
                    	   00，水平寻址模式;01，垂直寻址模式;10，页面寻址模式（重置）;11，无效*/
	OLED_ComWrite(0xb0); /*Set Page Start Address for Page Addressing Mode,0-7
                    	   设置页面寻址模式的页面起始地址，0-7*/
	OLED_ComWrite(0xc8); /*Set COM Output Scan Direction 设置 COM 输出扫描方向*/
	OLED_ComWrite(0x00); /*--set low column address 设置低列地址*/
	OLED_ComWrite(0x10); /*--set high column address 设置高列地址*/
	OLED_ComWrite(0x40); /*--set start line address 设置起跑线地址*/
	OLED_ComWrite(0x81); /*--set contrast control register 设置对比度控制寄存器*/
	OLED_ComWrite(0xff); /*亮度调节 0x00~0xff*/
	OLED_ComWrite(0xa1); /*--set segment re-map 0 to 127 将段重新映射 0 设置为 127*/
	OLED_ComWrite(0xa6); /*--set normal display 设置正常显示*/
	OLED_ComWrite(0xa8); /*--set multiplex ratio(1 to 64) 设置多重比（1 至 64）*/
	OLED_ComWrite(0x3F); 
	OLED_ComWrite(0xa4); /*0xa4,Output follows RAM content;0xa5,Output ignores RAM content
                    	 输出跟随RAM内容;0xa5，输出忽略RAM内容*/
	OLED_ComWrite(0xd3); /*--set display offset 设置显示偏移*/
	OLED_ComWrite(0x00); /*--not offset 关闭偏移*/
	OLED_ComWrite(0xd5); /*--set display clock divide ratio/oscillator frequency
                    	 	 设置显示时钟分频比/振荡器频率*/
	OLED_ComWrite(0xf0); /*--set divide ratio 设置分频比*/
	OLED_ComWrite(0xd9); /*--set pre-charge period 设置预充电周期*/
	OLED_ComWrite(0x22); 
	OLED_ComWrite(0xda); /*--set com pins hardware configuration 设置 COM 引脚硬件配置*/
	OLED_ComWrite(0x12);
	OLED_ComWrite(0xdb); /*--set vcomh 设置vcomh*/
	OLED_ComWrite(0x20); /*0x20,0.77xVcc*/
	OLED_ComWrite(0x8d); /*--set DC-DC enable 设置直流-直流使能*/
	OLED_ComWrite(0x14); 
	OLED_ComWrite(0xaf); /*--turn on oled panel 打开 OLED 面板*/

}

 /**
 * @brief 全屏填充操作
 * @param fill_Data：填充数据
 * @retval None
*/
void OLED_Fill(uint8_t fill_Data)
{
	uint8_t m,n;
	for(m=0;m<8;m++)
	{
		OLED_ComWrite(0xb0+m);		/*page0-pagem 0~m页*/
		OLED_ComWrite(0x00);		/*low column start address 低列起始地址*/
		OLED_ComWrite(0x10);		/*high column start address 高列起始地址*/
		for(n=0;n<128;n++)
			{
				OLED_DataWrite(fill_Data);
			}
	}
}

/**
 * @brief 起始点X,Y坐标设置
 * @param x 起始点X坐标数值
 * @param y 起始点y坐标数值
 * @retval None
*/
void OLED_SetPos(uint8_t x, uint8_t y) 
{ 
	OLED_ComWrite(0xb0+y);
	OLED_ComWrite(((x&0xf0)>>4)|0x10);
	OLED_ComWrite((x&0x0f)|0x01);
}

/**
 * @brief 清空所有OLED显示内容
 * @param None
 * @retval None
*/
void OLED_CLS(void)
{
	OLED_Fill(0x00);
}

/**
  * @brief  开启OLED
  * @param  None
  * @retval None
  */
 void OLED_ON (void)
 {
	OLED_ComWrite(0x8D); /*设置电荷泵*/
	OLED_ComWrite(0x14); /*开启电荷泵*/
	OLED_ComWrite(0xAF); /*唤醒OLED*/
 }

 /**
  * @brief  关闭OLED
  * @param  None
  * @retval None
  */
 void OLED_OFF (void)
 {
	OLED_ComWrite(0x80); /*设置电荷泵*/
	OLED_ComWrite(0x10); /*关闭电荷泵*/ 
	OLED_ComWrite(0xAE); /*OLED休眠*/

 }
 /**
  * @ }
 */

/**
 * @addtogroup OLED各类显示操作API
 * @{
*/	

/**
 * @brief 用于显示字符串
 * @param x：起始点横坐标 范围：0~127
 * @param y：起始点纵坐标 范围：0~7
 * @param ch[]：要显示的字符串
 * @param TextSize： 字符大小
 *			可以为： 1 （6*8）
 *					2 （8*16）
 * @retval None
*/
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
{
	uint8_t c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_DataWrite(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_DataWrite(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_DataWrite(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

/**
 * @brief
 * @param x：起始点横坐标 范围：0~127
 * @param y：起始点纵坐标 范围：0~7
 * @param N：汉字在asc.h(ASCII码)中的索引
 * @retval None
*/
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t N)
{
	uint8_t wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_DataWrite(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_DataWrite(F16x16[adder]);
		adder += 1;
	}
}

/**
 * @brief
 * @param x：起始点横坐标 范围：0~127
 * @param y：起始点纵坐标 范围：0~7
 * @param N：汉字在asc.h(ASCII码)中的索引
 * @retval None
*/
void OLED_ShowCN2(uint8_t x, uint8_t y, uint8_t N)
{
	uint8_t wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_DataWrite(F16x16_2[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_DataWrite(F16x16_2[adder]);
		adder += 1;
	}
}

/**
 * @brief
 * @param x：起始点横坐标 范围：0~127
 * @param y：起始点纵坐标 范围：0~7
 * @param N：汉字在asc.h(ASCII码)中的索引
 * @retval None
*/
void OLED_ShowCN3(uint8_t x, uint8_t y, uint8_t N)
{
	uint8_t wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_DataWrite(F16x16_3[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_DataWrite(F16x16_3[adder]);
		adder += 1;
	}
}


/**
 * @brief 这是自己写的显示中文字符串的函数，要先把中文字符串“共阴——列行式——逆向输出”取字模后存入asc.h相应的位置(连续存入)
 * @param x:起始横坐标  范围：0~127
 * @param y:起始纵坐标  范围：0~7
 * @param begin:填入的中文字符串的第一个字在我们asc.h字库里面的序号
 * @param num:我们要填写几个字 最多7个
 * @note 比如要填“测试”，取完字模存入后这两个字在字库中序号为0,1,横坐标0，纵坐标第二行，就填：x：0，y：2，begin：0，num：2
 * @retval None
*/
void OLED_ShowCN_STR(uint8_t x , uint8_t y , uint8_t begin , uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++){OLED_ShowCN(i*16+x,y,i+begin);}    //OLED显示标题
}
void OLED_ShowCN_STR2(uint8_t x , uint8_t y , uint8_t begin , uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++){OLED_ShowCN2(i*16+x,y,i+begin);}    //OLED显示标题
}

void OLED_ShowCN_STR3(uint8_t x , uint8_t y , uint8_t begin , uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++){OLED_ShowCN3(i*16+x,y,i+begin);}    //OLED显示标题
}
/**
 * @}
*/
