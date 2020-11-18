#include <stdio.h>
#include "my_string.h"

/*
 *  功  能: 将LoRa收到的数据包 拷贝到临时的2K缓冲区中
 *  param1: 指向要拷贝的目标地址的指针
 *  param2: 指向要拷贝的源地址的指针
 *  param3: 要拷贝的数据的长度
 *  retval: 无
 * 
 *  说  明: 因为升级的数据包中可能存在数据 0x00，因此不能使用库函数 strcpy
 */
void MyStrncpy(uint8_t *des, uint8_t *src, uint8_t len)
{
    uint8_t i;
    
    if( (des == NULL) || (src == NULL) )
        return;
    
    for(i=0; i<len; ++i)
    {
        *des = *src;
        des++;
        src++;
    }
}


/*
 *  功  能: 用于MD5的校验比较
 *  param1: 指向要校验的目标地址的指针
 *  param2: 指向要校验的源地址的指针
 *  param3: 要校验的数据的长度
 *  retval: 0表示两者数据一样，-1表示不一样
 * 
 *  说  明: 因为升级的数据包中可能存在数据 0x00，因此不能使用库函数 strcpy
 */
int MyStrncmp(uint8_t *des, uint8_t *src, uint8_t len)
{
    int i;
    
    if( (des == NULL) || (src == NULL) )
        return -1;
    
    for(i=0; i<len; ++i)
    {
        if(*des != *src)
        {
            return -1;
        }
        des++;
        src++;
    }
    
    return 0;
}