

#include "Key.h"
#include "OLED.h"

KEY_StateTypeDef Allkey;

uint8_t flag1 = 0,falg2 = 0,flag3;

void Key_Scan(KEY_StateTypeDef *allkey)
{


    if ((!KEY1_RESET)&&(!KEY2_RESET))
    {
            
        if (flag3<3)
        {
            /* code */
            flag3++;
            allkey->Memu = flag3;
            OLED_Clear();
            for (uint8_t i = 0; i < 100; i++)
            {
                /* code */
            }
            
        }
        else
        {
            flag3 =0;
        }
        
    }

    
        if (allkey->Memu == 1)
        {
            /* code */
                if((!KEY1_RESET) || (!KEY2_RESET))
            {
                if (!KEY1_RESET)
                {
                    /* code */
                    if (flag1 <4)
                    {
                        /* code */
                        flag1++;
                        allkey->key1.Flag = flag1;
                        for (size_t i = 0; i < 100; i++)
                        {
                            /* code */
                        }

                    }
                    else
                    {
                        flag1 =0;
                    }
                    
                }
                else if (!KEY2_RESET)
                {
                    /* code */ 
                falg2 = !falg2;
                }
    
            }
        }
    
    
}
