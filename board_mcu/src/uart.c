#include <stdio.h>
//#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include "uart.h"


/*!
 *  功  能: 恢复串口1-4 寄存器到默认值
 *  param1: 无
 *  retval: 无
 */
void UartDeInit(void)
{
    USART_DeInit(USART1);
    USART_DeInit(USART2);
    USART_DeInit(USART3);
    USART_DeInit(UART4);
}


/*!
 *  功  能: 串口的初始化
 *  param1: 要初始化的串口对象，在 uart.h 中定义
 *  param2: 串口号 UART_1、UART2_1、等等，在 uart.h 中定义
 *  param3: 串口的TX引脚，在 pinNane_boad.h 中定义
 *  param4: 串口的RX引脚，在 pinNane_boad.h 中定义
 *  retval: 无返回值 
 *
 *  注  意: 对于重映射的串口，本程序尚未考虑，使用的均为引脚的默认功能
 */
void UartInit( Uart_t *obj, UartIDs uartId, PinNames tx, PinNames rx )
{
    // UART的ID号
    if(uartId == UART_1)
    {
        obj->UartId = USART1;
        USART_DeInit(USART1);       // 恢复寄存器到默认值
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  // 使能串口1的时钟
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


    GpioInit( &obj->Tx, tx, PIN_Mode_AF_PP, 0 );    // 初始化 TX 引脚
    GpioInit( &obj->Rx, rx, PIN_Mode_IPU, 0 );      // 初始化 RX 引脚    
}


/*!
 *  功  能: 串口的配置
 *  param1: 要配置的串口对象，在 uart.h 中定义
 *  param2: 串口收发模式，在 uart.h 中定义
 *  param3: 串口的波特率，在 uart.h 中定义
 *  param4: 串口的数据长度，在 uart.h 中定义
 *  param5: 串口的停止位个数，在 uart.h 中定义
 *  param6: 串口的校验位配置，在 uart.h 中定义
 *  param7: 串口的流控配置，在 uart.h 中定义
 *  retval: 无返回值 
 * 
 *  注  意: 对于重映射的串口，本程序尚未考虑，使用的均为引脚的默认功能
 */
void UartConfig( Uart_t *obj, UartModes mode, uint32_t baudrate, WordLengthes wordLength, StopBits stopBits, Parities parity, FlowCtrls flowCtrl )
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudrate;
    
    // 收发模式设置
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


    // 数据长度设置
    if( wordLength == UART_8_BIT )
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    }
    else if( wordLength == UART_9_BIT )
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
    }


    // 停止位设置
    if(stopBits == UART_1_STOP_BIT)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    else if(stopBits == UART_2_STOP_BIT)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
    }


    // 校验位
    if( parity == NO_PARITY )
    {
        USART_InitStructure.USART_Parity = USART_Parity_No; // 无校验
    }
    else if( parity == EVEN_PARITY )
    {
        USART_InitStructure.USART_Parity = EVEN_PARITY;     // 偶校验
    }
    else
    {
        USART_InitStructure.USART_Parity = ODD_PARITY;     // 奇校验
    }

    // 流控设置
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
    
    USART_Init(obj->UartId, &USART_InitStructure);  // 初始化串口
    USART_Cmd(obj->UartId, ENABLE);                 // 使能串口
}


/*!
 *  功  能: 串口的中断配置
 *  param1: 要配置的串口对象，在 uart.h 中定义
 *  param2: 抢占优先级，注意与中断优先级分组相对应
 *  param3: 子优先级，注意与中断优先级分组相对应
 *  retval: 无返回值 
 *  
 *  注意！！！: 本工程中串口的中断默认接收和空闲中断同时使能
 *  注意！！！: 中断优先级分组在 main.c 一开始定义，全工程只定义一次
 */
void UartSetInterrupt(Uart_t *obj, uint8_t preemptionPriority, uint8_t subPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             // 使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;                // 子优先级
    
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
    NVIC_Init(&NVIC_InitStructure);                     // 嵌套向量中断控制器初始化
    
//    USART_ITConfig(obj->UartId, USART_IT_RXNE, ENABLE); // 使能串口接收中断	
    USART_ITConfig(obj->UartId, USART_IT_IDLE, ENABLE); // 使能串口空闲中断
    
//    USART_ITConfig(obj->UartId, USART_IT_CTS,  DISABLE);
//    USART_ITConfig(obj->UartId, USART_IT_LBD,  DISABLE);
//    USART_ITConfig(obj->UartId, USART_IT_TXE,  DISABLE);
    USART_ITConfig(obj->UartId, USART_IT_TC,   ENABLE);
//    USART_ITConfig(obj->UartId, USART_IT_PE,   DISABLE);
//    USART_ITConfig(obj->UartId, USART_IT_ERR,  DISABLE);

    // 使能串口
    USART_Cmd(obj->UartId, ENABLE);
}


/*!
 *  功  能: 使能串口的空闲中断
 *  param1: 无
 *  retval: 无
 */
void UartIdleEnable(Uart_t *obj)
{
    USART_ITConfig(obj->UartId, USART_IT_IDLE, ENABLE); // 使能串口空闲中断
}


/*!
 *  功  能: 禁止串口的空闲中断
 *  param1: 无
 *  retval: 无
 */
void UartIdleDisable(Uart_t *obj)
{
    USART_ITConfig(obj->UartId, USART_IT_IDLE, DISABLE); // 禁止串口空闲中断
}


/*!
 *  功  能: 返回串口收到的数据
 *  param1: 无
 *  retval: 串口收到的数据 
 */
uint16_t UartRecvData(Uart_t *obj)
{
    return USART_ReceiveData( obj->UartId );
}


/*!
 *  功  能: 串口发送一个字符
 *  param1: 要使用的串口对象，在 uart.h 中定义
 *  param2: 要发送的字符数据
 *  retval: 无返回值 
 */
void UartSendChar(Uart_t *obj, uint8_t data)
{
    USART_SendData(obj->UartId, data);     // 发送一个字节数据到USART

    while (USART_GetFlagStatus(obj->UartId, USART_FLAG_TXE) == RESET);  // 等待发送数据寄存器为空
}


/*!
 *  功  能: 串口发送字符串
 *  param1: 要使用的串口对象，在 uart.h 中定义
 *  param2: 要发送的字符串数据
 *  retval: 无返回值 
 */
void UartSendString(Uart_t *obj, uint8_t *str)
{
    while(*str != '\0')
    { 
        UartSendChar(obj, *str);
        str++;
    }
    
    while(USART_GetFlagStatus(obj->UartId, USART_FLAG_TC)==RESET);      // 等待发送完成   
}


/*!
 *  功  能: 串口发送字符数组
 *  param1: 要使用的串口对象，在 uart.h 中定义
 *  param2: 要发送的字符数组
 *  param3: 要发送的字符数组的长度
 *  retval: 无返回值 
 */
void UartSendArray(Uart_t *obj, uint8_t *array, uint8_t len)
{
    uint8_t i;
    
    for(i=0; i<len; i++)
    {
        UartSendChar(obj, array[i]);	
    }
    
    while(USART_GetFlagStatus(obj->UartId, USART_FLAG_TC) == RESET);       // 等待发送完成
}


/*!
 *  功  能: 获取串口中断的状态
 *  param1: 要操作的串口对象
 *  param2: 要获取的串口中断的种类
 *  retval: RESET = 0, SET = !RESET
 */
ITStatus UartGetIntStatus(Uart_t *obj, UartIntStatuses intStatus)
{
    switch(intStatus)
    {
    case PIN_UART_FLAG_TXE:
        return USART_GetITStatus(obj->UartId, USART_IT_TXE);  // 发送寄存器非空
        break;
    case PIN_UART_FLAG_TC:
        return USART_GetITStatus(obj->UartId, USART_IT_TC);   // 发送完成
        break;
    case PIN_UART_FLAG_RXNE:
        return USART_GetITStatus(obj->UartId, USART_IT_RXNE); // 接收寄存器非空
        break;
    case PIN_UART_FLAG_IDLE:
        return USART_GetITStatus(obj->UartId, USART_IT_IDLE); // 空闲中断
        break;
    case PIN_UART_FLAG_ORE:
        return USART_GetITStatus(obj->UartId, USART_IT_ORE);
    default:
        break;
    }
    
    return RESET;
}


/*!
 *  功  能: 清除串口中断标志位
 *  param1: 要操作的串口对象
 *  param2: 要清除的串口中断的种类
 *  retval: 无返回值
 */
void UartClearIntFlag(Uart_t *obj, UartIntStatuses uartFlag)
{
    uint8_t clear;
    
    switch(uartFlag)
    {
    case PIN_UART_FLAG_TC:    // 发送完成
        USART_ClearITPendingBit(obj->UartId, USART_IT_TC);      // 清除中断标志
        break;
    case PIN_UART_FLAG_RXNE:  // 接收数据寄存器非空
        USART_ClearITPendingBit(obj->UartId, USART_IT_RXNE);      // 清除中断标志
        break;
    case PIN_UART_FLAG_IDLE:     // 接收空闲中断
        clear = obj->UartId->SR;    // 先读SR
        clear = obj->UartId->DR;    // 再读DR
        break;
    case PIN_UART_FLAG_ORE:
        clear = obj->UartId->SR;
        clear = obj->UartId->CR1;
    default:
        break;
    }
    
}



