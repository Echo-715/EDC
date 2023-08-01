#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"


typedef struct 
{
    /* data */
    struct 
    {
        uint8_t Flag;
    }key1;
    struct 
    {
        uint8_t Flag;       
    }key2;

    uint8_t Memu;

}KEY_StateTypeDef;


extern KEY_StateTypeDef Allkey;


void Key_Scan(KEY_StateTypeDef *allkey);

#endif
