#include <stdio.h>
//#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include "uart.h"


/*!
 *  ��  ��: �ָ�����1-4 �Ĵ�����Ĭ��ֵ
 *  param1: ��
 *  retval: ��
 */
void UartDeInit(void)
{
    USART_DeInit(USART1);
    USART_DeInit(USART2);
    USART_DeInit(USART3);
    USART_DeInit(UART4);
}


/*!
 *  ��  ��: ���ڵĳ�ʼ��
 *  param1: Ҫ��ʼ���Ĵ��ڶ����� uart.h �ж���
 *  param2: ���ں� UART_1��UART2_1���ȵȣ��� uart.h �ж���
 *  param3: ���ڵ�TX���ţ��� pinNane_boad.h �ж���
 *  param4: ���ڵ�RX���ţ��� pinNane_boad.h �ж���
 *  retval: �޷���ֵ 
 *
 *  ע  ��: ������ӳ��Ĵ��ڣ���������δ���ǣ�ʹ�õľ�Ϊ���ŵ�Ĭ�Ϲ���
 */
void UartInit( Uart_t *obj, UartIDs uartId, PinNames tx, PinNames rx )
{
    // UART��ID��
    if(uartId == UART_1)
    {
        obj->UartId = USART1;
        USART_DeInit(USART1);       // �ָ��Ĵ�����Ĭ��ֵ
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  // ʹ�ܴ���1��ʱ��
    }
    else if(uartId == UART_2)
    {
        obj->UartId = USART2;
        USART_DeInit(USART2);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    }
    else if(uartId == UART_3)
    {
        obj->UartId = USART3;
        USART_DeInit(USART3);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    }
    else if(uartId == UART_4)
    {
        obj->UartId = UART4;
        USART_DeInit(UART4);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    }


    GpioInit( &obj->Tx, tx, PIN_Mode_AF_PP, 0 );    // ��ʼ�� TX ����
    GpioInit( &obj->Rx, rx, PIN_Mode_IPU, 0 );      // ��ʼ�� RX ����    
}


/*!
 *  ��  ��: ���ڵ�����
 *  param1: Ҫ���õĴ��ڶ����� uart.h �ж���
 *  param2: �����շ�ģʽ���� uart.h �ж���
 *  param3: ���ڵĲ����ʣ��� uart.h �ж���
 *  param4: ���ڵ����ݳ��ȣ��� uart.h �ж���
 *  param5: ���ڵ�ֹͣλ�������� uart.h �ж���
 *  param6: ���ڵ�У��λ���ã��� uart.h �ж���
 *  param7: ���ڵ��������ã��� uart.h �ж���
 *  retval: �޷���ֵ 
 * 
 *  ע  ��: ������ӳ��Ĵ��ڣ���������δ���ǣ�ʹ�õľ�Ϊ���ŵ�Ĭ�Ϲ���
 */
void UartConfig( Uart_t *obj, UartModes mode, uint32_t baudrate, WordLengthes wordLength, StopBits stopBits, Parities parity, FlowCtrls flowCtrl )
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudrate;
    
    // �շ�ģʽ����
    if( mode == TX_ONLY )
    {
        USART_InitStructure.USART_Mode = USART_Mode_Tx;
    }
    else if( mode == RX_ONLY )
    {
        USART_InitStructure.USART_Mode = USART_Mode_Rx;
    }
    else if( mode == RX_TX )
    {
        USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    }


    // ���ݳ�������
    if( wordLength == UART_8_BIT )
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    }
    else if( wordLength == UART_9_BIT )
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
    }


    // ֹͣλ����
    if(stopBits == UART_1_STOP_BIT)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    else if(stopBits == UART_2_STOP_BIT)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
    }


    // У��λ
    if( parity == NO_PARITY )
    {
        USART_InitStructure.USART_Parity = USART_Parity_No; // ��У��
    }
    else if( parity == EVEN_PARITY )
    {
        USART_InitStructure.USART_Parity = EVEN_PARITY;     // żУ��
    }
    else
    {
        USART_InitStructure.USART_Parity = ODD_PARITY;     // ��У��
    }

    // ��������
    if( flowCtrl == NO_FLOW_CTRL )
    {
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    }
    else if( flowCtrl == RTS_FLOW_CTRL )
    {
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
    }
    else if( flowCtrl == CTS_FLOW_CTRL )
    {
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_CTS;
    }
    else if( flowCtrl == RTS_CTS_FLOW_CTRL )
    {
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
    }
    
    USART_Init(obj->UartId, &USART_InitStructure);  // ��ʼ������
    USART_Cmd(obj->UartId, ENABLE);                 // ʹ�ܴ���
}


/*!
 *  ��  ��: ���ڵ��ж�����
 *  param1: Ҫ���õĴ��ڶ����� uart.h �ж���
 *  param2: ��ռ���ȼ���ע�����ж����ȼ��������Ӧ
 *  param3: �����ȼ���ע�����ж����ȼ��������Ӧ
 *  retval: �޷���ֵ 
 *  
 *  ע�⣡����: �������д��ڵ��ж�Ĭ�Ͻ��պͿ����ж�ͬʱʹ��
 *  ע�⣡����: �ж����ȼ������� main.c һ��ʼ���壬ȫ����ֻ����һ��
 */
void UartSetInterrupt(Uart_t *obj, uint8_t preemptionPriority, uint8_t subPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             // ʹ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;                // �����ȼ�
    
    if(obj->UartId == USART1)
    {
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    }
    else if(obj->UartId == USART2)
    {
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    }
    else if(obj->UartId == USART3)
    {
        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    }
    else if(obj->UartId == UART4)
    {
        NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    }
    NVIC_Init(&NVIC_InitStructure);                     // Ƕ�������жϿ�������ʼ��
    
//    USART_ITConfig(obj->UartId, USART_IT_RXNE, ENABLE); // ʹ�ܴ��ڽ����ж�	
    USART_ITConfig(obj->UartId, USART_IT_IDLE, ENABLE); // ʹ�ܴ��ڿ����ж�
    
//    USART_ITConfig(obj->UartId, USART_IT_CTS,  DISABLE);
//    USART_ITConfig(obj->UartId, USART_IT_LBD,  DISABLE);
//    USART_ITConfig(obj->UartId, USART_IT_TXE,  DISABLE);
    USART_ITConfig(obj->UartId, USART_IT_TC,   ENABLE);
//    USART_ITConfig(obj->UartId, USART_IT_PE,   DISABLE);
//    USART_ITConfig(obj->UartId, USART_IT_ERR,  DISABLE);

    // ʹ�ܴ���
    USART_Cmd(obj->UartId, ENABLE);
}


/*!
 *  ��  ��: ʹ�ܴ��ڵĿ����ж�
 *  param1: ��
 *  retval: ��
 */
void UartIdleEnable(Uart_t *obj)
{
    USART_ITConfig(obj->UartId, USART_IT_IDLE, ENABLE); // ʹ�ܴ��ڿ����ж�
}


/*!
 *  ��  ��: ��ֹ���ڵĿ����ж�
 *  param1: ��
 *  retval: ��
 */
void UartIdleDisable(Uart_t *obj)
{
    USART_ITConfig(obj->UartId, USART_IT_IDLE, DISABLE); // ��ֹ���ڿ����ж�
}


/*!
 *  ��  ��: ���ش����յ�������
 *  param1: ��
 *  retval: �����յ������� 
 */
uint16_t UartRecvData(Uart_t *obj)
{
    return USART_ReceiveData( obj->UartId );
}


/*!
 *  ��  ��: ���ڷ���һ���ַ�
 *  param1: Ҫʹ�õĴ��ڶ����� uart.h �ж���
 *  param2: Ҫ���͵��ַ�����
 *  retval: �޷���ֵ 
 */
void UartSendChar(Uart_t *obj, uint8_t data)
{
    USART_SendData(obj->UartId, data);     // ����һ���ֽ����ݵ�USART

    while (USART_GetFlagStatus(obj->UartId, USART_FLAG_TXE) == RESET);  // �ȴ��������ݼĴ���Ϊ��
}


/*!
 *  ��  ��: ���ڷ����ַ���
 *  param1: Ҫʹ�õĴ��ڶ����� uart.h �ж���
 *  param2: Ҫ���͵��ַ�������
 *  retval: �޷���ֵ 
 */
void UartSendString(Uart_t *obj, uint8_t *str)
{
    while(*str != '\0')
    { 
        UartSendChar(obj, *str);
        str++;
    }
    
    while(USART_GetFlagStatus(obj->UartId, USART_FLAG_TC)==RESET);      // �ȴ��������   
}


/*!
 *  ��  ��: ���ڷ����ַ�����
 *  param1: Ҫʹ�õĴ��ڶ����� uart.h �ж���
 *  param2: Ҫ���͵��ַ�����
 *  param3: Ҫ���͵��ַ�����ĳ���
 *  retval: �޷���ֵ 
 */
void UartSendArray(Uart_t *obj, uint8_t *array, uint8_t len)
{
    uint8_t i;
    
    for(i=0; i<len; i++)
    {
        UartSendChar(obj, array[i]);	
    }
    
    while(USART_GetFlagStatus(obj->UartId, USART_FLAG_TC) == RESET);       // �ȴ��������
}


/*!
 *  ��  ��: ��ȡ�����жϵ�״̬
 *  param1: Ҫ�����Ĵ��ڶ���
 *  param2: Ҫ��ȡ�Ĵ����жϵ�����
 *  retval: RESET = 0, SET = !RESET
 */
ITStatus UartGetIntStatus(Uart_t *obj, UartIntStatuses intStatus)
{
    switch(intStatus)
    {
    case PIN_UART_FLAG_TXE:
        return USART_GetITStatus(obj->UartId, USART_IT_TXE);  // ���ͼĴ����ǿ�
        break;
    case PIN_UART_FLAG_TC:
        return USART_GetITStatus(obj->UartId, USART_IT_TC);   // �������
        break;
    case PIN_UART_FLAG_RXNE:
        return USART_GetITStatus(obj->UartId, USART_IT_RXNE); // ���ռĴ����ǿ�
        break;
    case PIN_UART_FLAG_IDLE:
        return USART_GetITStatus(obj->UartId, USART_IT_IDLE); // �����ж�
        break;
    case PIN_UART_FLAG_ORE:
        return USART_GetITStatus(obj->UartId, USART_IT_ORE);
    default:
        break;
    }
    
    return RESET;
}


/*!
 *  ��  ��: ��������жϱ�־λ
 *  param1: Ҫ�����Ĵ��ڶ���
 *  param2: Ҫ����Ĵ����жϵ�����
 *  retval: �޷���ֵ
 */
void UartClearIntFlag(Uart_t *obj, UartIntStatuses uartFlag)
{
    uint8_t clear;
    
    switch(uartFlag)
    {
    case PIN_UART_FLAG_TC:    // �������
        USART_ClearITPendingBit(obj->UartId, USART_IT_TC);      // ����жϱ�־
        break;
    case PIN_UART_FLAG_RXNE:  // �������ݼĴ����ǿ�
        USART_ClearITPendingBit(obj->UartId, USART_IT_RXNE);      // ����жϱ�־
        break;
    case PIN_UART_FLAG_IDLE:     // ���տ����ж�
        clear = obj->UartId->SR;    // �ȶ�SR
        clear = obj->UartId->DR;    // �ٶ�DR
        break;
    case PIN_UART_FLAG_ORE:
        clear = obj->UartId->SR;
        clear = obj->UartId->CR1;
    default:
        break;
    }
    
}



