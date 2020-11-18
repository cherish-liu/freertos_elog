#ifndef _UART_H_
#define _UART_H_

#include "gpio.h"


/* 串口结构体 */
typedef struct
{
    USART_TypeDef *UartId;
    Gpio_t Tx;
    Gpio_t Rx;
}Uart_t;


typedef enum
{
    UART_1 = 0, // 串口1，USART1
    UART_2,     // 串口2，USART2
    UART_3,     // 串口3，USART3
    UART_4      // 串口4，UART4
}UartIDs;


/* 串口模式 */
typedef enum
{
    TX_ONLY = 0,    // 只发送
    RX_ONLY,        // 只接收
    RX_TX           // 收发一体
}UartModes;


/* 数据长度，数据长度=有效数据长度+校验位 */
typedef enum
{
    UART_8_BIT = 0, // 8
    UART_9_BIT      // 9
}WordLengthes;


/* 停止位 */
typedef enum
{
    UART_1_STOP_BIT = 0,    // 1个停止位
    UART_0_5_STOP_BIT,      // 不使用
    UART_2_STOP_BIT,        // 2个停止位
    UART_1_5_STOP_BIT       // 不使用
}StopBits;


/* 奇偶检验位 */
typedef enum
{
    NO_PARITY = 0,          // 无校验位
    EVEN_PARITY,            // 偶校验，保证1的个数是偶数个
    ODD_PARITY              // 奇校验
}Parities;


/* 流控 */
typedef enum
{
    NO_FLOW_CTRL = 0,
    RTS_FLOW_CTRL,
    CTS_FLOW_CTRL,
    RTS_CTS_FLOW_CTRL
}FlowCtrls;


/* 中断状态 */
typedef enum
{
    PIN_UART_FLAG_TXE = 0, 
    PIN_UART_FLAG_TC,  
    PIN_UART_FLAG_RXNE,
    PIN_UART_FLAG_IDLE,
    PIN_UART_FLAG_ORE
}UartIntStatuses;


void UartDeInit(void);

void UartInit( Uart_t *obj, UartIDs uartId, PinNames tx, PinNames rx );

void UartConfig( Uart_t *obj, UartModes mode, uint32_t baudrate, WordLengthes wordLength, StopBits stopBits, Parities parity, FlowCtrls flowCtrl );

void UartSetInterrupt(Uart_t *obj, uint8_t preemptionPriority, uint8_t subPriority);

void UartIdleEnable(Uart_t *obj);

void UartIdleDisable(Uart_t *obj);

uint16_t UartRecvData(Uart_t *obj);

void UartSendChar(Uart_t *obj, uint8_t data);

void UartSendString(Uart_t *obj, uint8_t *str);

void UartSendArray(Uart_t *obj, uint8_t *array, uint8_t len);

ITStatus UartGetIntStatus(Uart_t *obj, UartIntStatuses intStatus);

void UartClearIntFlag(Uart_t *obj, UartIntStatuses uartFlag);




#endif  /* uart.h */