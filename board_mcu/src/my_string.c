#include <stdio.h>
#include "my_string.h"

/*
 *  ��  ��: ��LoRa�յ������ݰ� ��������ʱ��2K��������
 *  param1: ָ��Ҫ������Ŀ���ַ��ָ��
 *  param2: ָ��Ҫ������Դ��ַ��ָ��
 *  param3: Ҫ���������ݵĳ���
 *  retval: ��
 * 
 *  ˵  ��: ��Ϊ���������ݰ��п��ܴ������� 0x00����˲���ʹ�ÿ⺯�� strcpy
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
 *  ��  ��: ����MD5��У��Ƚ�
 *  param1: ָ��ҪУ���Ŀ���ַ��ָ��
 *  param2: ָ��ҪУ���Դ��ַ��ָ��
 *  param3: ҪУ������ݵĳ���
 *  retval: 0��ʾ��������һ����-1��ʾ��һ��
 * 
 *  ˵  ��: ��Ϊ���������ݰ��п��ܴ������� 0x00����˲���ʹ�ÿ⺯�� strcpy
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