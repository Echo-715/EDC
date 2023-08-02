
#include "Key.h"
#include "OLED.h"

KEY_StateTypeDef Allkey;

uint8_t flag1 = 1,falg2 = 0,flag3= 0;

void Key_Scan(KEY_StateTypeDef *allkey)
{
    allkey->key1.Flag = flag1;


    /* code */
    if((!KEY1_RESET) || (!KEY2_RESET))
    {
        if (!KEY2_RESET)
        {

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
    
    

