/**
  ******************************************************************************
  * @file   OLED.c
  * @brief  �ṩOLEDʹ�õĳ�ʼ�����������ã��Լ�����Ӧ�÷�װ
  ******************************************************************************
  * @attention
  * 
  *  None
  *
  ******************************************************************************  
**/
/* Private includes �ǹٷ�ͷ�ļ�����----------------------------------------------------------*/
#include "OLED.h"
#include "asc.h"
/* Exported types ���Ͷ���------------------------------------------------------------*/
/* Exported constants ��������--------------------------------------------------------*/
/* Exported macro �궨��------------------------------------------------------------*/
/* Exported functions prototypes ��������---------------------------------------------*/
/**
 * @addtogroup OLED��ʼ������������API
 * @{
*/
/**
  * @brief  OLED����д�뺯��
  * @param  IIC_Command д���ָ��
  * @retval None
  */
void OLED_ComWrite(uint8_t IIC_Command) 
{
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,COMM,I2C_MEMADD_SIZE_8BIT,&IIC_Command,1,100);
}

/**
  * @brief  OLED����д�뺯��
  * @param  IIC_Data��д�������
  * @note   ���ݴ�СΪһ���ֽ�
  * @retval None
  */
void OLED_DataWrite(uint8_t IIC_Data) 
{
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,DATA,I2C_MEMADD_SIZE_8BIT,&IIC_Data,1,100);
}

/**
  * @brief  OLED��ʼ������
  * @param  None
  * @retval None
  */
void OLED_Init(void)
{
	HAL_Delay(100); //�������ʱ����Ҫ
	
	OLED_ComWrite(0xAE); /*display off ��ʾ�ر�*/
	OLED_ComWrite(0x20); /*Set Memory Addressing Mode �����ڴ�Ѱַģʽ*/
	OLED_ComWrite(0x10); /*00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
                    	   00��ˮƽѰַģʽ;01����ֱѰַģʽ;10��ҳ��Ѱַģʽ�����ã�;11����Ч*/
	OLED_ComWrite(0xb0); /*Set Page Start Address for Page Addressing Mode,0-7
                    	   ����ҳ��Ѱַģʽ��ҳ����ʼ��ַ��0-7*/
	OLED_ComWrite(0xc8); /*Set COM Output Scan Direction ���� COM ���ɨ�跽��*/
	OLED_ComWrite(0x00); /*--set low column address ���õ��е�ַ*/
	OLED_ComWrite(0x10); /*--set high column address ���ø��е�ַ*/
	OLED_ComWrite(0x40); /*--set start line address ���������ߵ�ַ*/
	OLED_ComWrite(0x81); /*--set contrast control register ���öԱȶȿ��ƼĴ���*/
	OLED_ComWrite(0xff); /*���ȵ��� 0x00~0xff*/
	OLED_ComWrite(0xa1); /*--set segment re-map 0 to 127 ��������ӳ�� 0 ����Ϊ 127*/
	OLED_ComWrite(0xa6); /*--set normal display ����������ʾ*/
	OLED_ComWrite(0xa8); /*--set multiplex ratio(1 to 64) ���ö��رȣ�1 �� 64��*/
	OLED_ComWrite(0x3F); 
	OLED_ComWrite(0xa4); /*0xa4,Output follows RAM content;0xa5,Output ignores RAM content
                    	 �������RAM����;0xa5���������RAM����*/
	OLED_ComWrite(0xd3); /*--set display offset ������ʾƫ��*/
	OLED_ComWrite(0x00); /*--not offset �ر�ƫ��*/
	OLED_ComWrite(0xd5); /*--set display clock divide ratio/oscillator frequency
                    	 	 ������ʾʱ�ӷ�Ƶ��/����Ƶ��*/
	OLED_ComWrite(0xf0); /*--set divide ratio ���÷�Ƶ��*/
	OLED_ComWrite(0xd9); /*--set pre-charge period ����Ԥ�������*/
	OLED_ComWrite(0x22); 
	OLED_ComWrite(0xda); /*--set com pins hardware configuration ���� COM ����Ӳ������*/
	OLED_ComWrite(0x12);
	OLED_ComWrite(0xdb); /*--set vcomh ����vcomh*/
	OLED_ComWrite(0x20); /*0x20,0.77xVcc*/
	OLED_ComWrite(0x8d); /*--set DC-DC enable ����ֱ��-ֱ��ʹ��*/
	OLED_ComWrite(0x14); 
	OLED_ComWrite(0xaf); /*--turn on oled panel �� OLED ���*/

}

 /**
 * @brief ȫ��������
 * @param fill_Data���������
 * @retval None
*/
void OLED_Fill(uint8_t fill_Data)
{
	uint8_t m,n;
	for(m=0;m<8;m++)
	{
		OLED_ComWrite(0xb0+m);		/*page0-pagem 0~mҳ*/
		OLED_ComWrite(0x00);		/*low column start address ������ʼ��ַ*/
		OLED_ComWrite(0x10);		/*high column start address ������ʼ��ַ*/
		for(n=0;n<128;n++)
			{
				OLED_DataWrite(fill_Data);
			}
	}
}

/**
 * @brief ��ʼ��X,Y��������
 * @param x ��ʼ��X������ֵ
 * @param y ��ʼ��y������ֵ
 * @retval None
*/
void OLED_SetPos(uint8_t x, uint8_t y) 
{ 
	OLED_ComWrite(0xb0+y);
	OLED_ComWrite(((x&0xf0)>>4)|0x10);
	OLED_ComWrite((x&0x0f)|0x01);
}

/**
 * @brief �������OLED��ʾ����
 * @param None
 * @retval None
*/
void OLED_CLS(void)
{
	OLED_Fill(0x00);
}

/**
  * @brief  ����OLED
  * @param  None
  * @retval None
  */
 void OLED_ON (void)
 {
	OLED_ComWrite(0x8D); /*���õ�ɱ�*/
	OLED_ComWrite(0x14); /*������ɱ�*/
	OLED_ComWrite(0xAF); /*����OLED*/
 }

 /**
  * @brief  �ر�OLED
  * @param  None
  * @retval None
  */
 void OLED_OFF (void)
 {
	OLED_ComWrite(0x80); /*���õ�ɱ�*/
	OLED_ComWrite(0x10); /*�رյ�ɱ�*/ 
	OLED_ComWrite(0xAE); /*OLED����*/

 }
 /**
  * @ }
 */

/**
 * @addtogroup OLED������ʾ����API
 * @{
*/	

/**
 * @brief ������ʾ�ַ���
 * @param x����ʼ������� ��Χ��0~127
 * @param y����ʼ�������� ��Χ��0~7
 * @param ch[]��Ҫ��ʾ���ַ���
 * @param TextSize�� �ַ���С
 *			����Ϊ�� 1 ��6*8��
 *					2 ��8*16��
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
 * @param x����ʼ������� ��Χ��0~127
 * @param y����ʼ�������� ��Χ��0~7
 * @param N��������asc.h(ASCII��)�е�����
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
 * @param x����ʼ������� ��Χ��0~127
 * @param y����ʼ�������� ��Χ��0~7
 * @param N��������asc.h(ASCII��)�е�����
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
 * @param x����ʼ������� ��Χ��0~127
 * @param y����ʼ�������� ��Χ��0~7
 * @param N��������asc.h(ASCII��)�е�����
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
 * @brief �����Լ�д����ʾ�����ַ����ĺ�����Ҫ�Ȱ������ַ�����������������ʽ�������������ȡ��ģ�����asc.h��Ӧ��λ��(��������)
 * @param x:��ʼ������  ��Χ��0~127
 * @param y:��ʼ������  ��Χ��0~7
 * @param begin:����������ַ����ĵ�һ����������asc.h�ֿ���������
 * @param num:����Ҫ��д������ ���7��
 * @note ����Ҫ����ԡ���ȡ����ģ����������������ֿ������Ϊ0,1,������0��������ڶ��У����x��0��y��2��begin��0��num��2
 * @retval None
*/
void OLED_ShowCN_STR(uint8_t x , uint8_t y , uint8_t begin , uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++){OLED_ShowCN(i*16+x,y,i+begin);}    //OLED��ʾ����
}
void OLED_ShowCN_STR2(uint8_t x , uint8_t y , uint8_t begin , uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++){OLED_ShowCN2(i*16+x,y,i+begin);}    //OLED��ʾ����
}

void OLED_ShowCN_STR3(uint8_t x , uint8_t y , uint8_t begin , uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++){OLED_ShowCN3(i*16+x,y,i+begin);}    //OLED��ʾ����
}
/**
 * @}
*/
