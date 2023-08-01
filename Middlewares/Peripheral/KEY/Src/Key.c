

#include "Key.h"
#include "OLED.h"

KEY_StateTypeDef Allkey;

uint8_t flag1 = 1,falg2 = 0,flag3= 0;

void Key_Scan(KEY_StateTypeDef *allkey)
{
    allkey->key1.Flag = flag1;
    if ((!KEY1_RESET)&&(!KEY2_RESET))
    {
        HAL_Delay(50);
        flag3++;
        if (flag3<2)
        {
            /* code */
            allkey->Memu = flag3;
            OLED_Clear();
            
        }
        else
        {
            flag3 =0;
            OLED_Clear();
            allkey->Memu = flag3;
        }
        
    }

    
        if (allkey->Memu == 1)
        {
            /* code */
            if((!KEY1_RESET) || (!KEY2_RESET))
            {
                if (!KEY2_RESET)
                {
                    HAL_Delay(10);
                    /* code */ 
                    falg2 = !falg2;
                    allkey->key2.Flag = falg2;

                    OLED_Clear();
                    
                    
                }
                if (allkey->key2.Flag == 0)
                {
                    /* code */
                    if (!KEY1_RESET)
                    {
                        /* code */
                        HAL_Delay(10);
                        if (flag1 <4)
                        {
                            /* code */
                            flag1++;
                            allkey->key1.Flag = flag1;

                        }
                        else
                        {
                            flag1 =1;
                            allkey->key1.Flag = flag1;
                        }
                        
                    }
    
            }


        }
        }
    
    
}
