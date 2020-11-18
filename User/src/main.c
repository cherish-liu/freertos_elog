#include <stdio.h>
#include <string.h>
#include "stm32f10x_usart.h"

#include "gpio.h"
#include "my_string.h"
#include "timer.h"
#include "rs485.h"

#include "FreeRTOS.h"
#include "task.h"
#include "mytask.h"

#define LOG_TAG "main"
#include "elog.h"

// ��������ĳ�ʼ��
void BoardPeriphInit(void)
{
    GpioDeInit();       // GPIO�Ĵ����ָ���Ĭ��ֵ
    ExtiDeInit();       // �ⲿ�жϼĴ����ָ���Ĭ��ֵ
    UartDeInit();       // �ĸ����ڼĴ����ָ���Ĭ��ֵ
    BasicTimerDeInit(); // ����������ʱ���Ĵ����ָ���Ĭ��ֵ
    
    SetNvicPriorityGroup( NVIC_PRIORITY_GROUP_4 );  // �����ж����ȼ�����
    
    BoardEnableIrq();           // ����ȫ���ж�
    ReserveLedInit();
    
    Rs485_A_Init();
    Rs485_A_TxEnable();
}


int main()
{  
    BoardPeriphInit();      // �����ʼ��
    
    if (elog_init() == ELOG_NO_ERR)
	{
        /* set enabled format */
        elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_T_INFO | ELOG_FMT_P_INFO));
        elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_T_INFO | ELOG_FMT_P_INFO));
		
        elog_set_text_color_enabled( true );
		
        elog_buf_enabled( false );
		
        /* start EasyLogger */
        elog_start();
	}
    log_a("Hello EasyLogger!");
    log_e("Hello EasyLogger!");
    log_w("Hello EasyLogger!");
    log_i("Hello EasyLogger!");
    log_d("Hello EasyLogger!");
    log_v("Hello EasyLogger!");
    CreateTask();
    
    
    while(1)
    {
        
    }
}

int fputc(int ch, FILE *f)
{
	/* Write a character to the USART */
	USART_SendData(USART1, ch);	// ��������
	
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	// ֱ���������
    
	return ch;
}



