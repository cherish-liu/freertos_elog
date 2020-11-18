#ifndef _UART_H_
#define _UART_H_

#include "gpio.h"


/* ���ڽṹ�� */
typedef struct
{
    USART_TypeDef *UartId;
    Gpio_t Tx;
    Gpio_t Rx;
}Uart_t;


typedef enum
{
    UART_1 = 0, // ����1��USART1
    UART_2,     // ����2��USART2
    UART_3,     // ����3��USART3
    UART_4      // ����4��UART4
}UartIDs;


/* ����ģʽ */
typedef enum
{
    TX_ONLY = 0,    // ֻ����
    RX_ONLY,        // ֻ����
    RX_TX           // �շ�һ��
}UartModes;


/* ���ݳ��ȣ����ݳ���=��Ч���ݳ���+У��λ */
typedef enum
{
    UART_8_BIT = 0, // 8
    UART_9_BIT      // 9
}WordLengthes;


/* ֹͣλ */
typedef enum
{
    UART_1_STOP_BIT = 0,    // 1��ֹͣλ
    UART_0_5_STOP_BIT,      // ��ʹ��
    UART_2_STOP_BIT,        // 2��ֹͣλ
    UART_1_5_STOP_BIT       // ��ʹ��
}StopBits;


/* ��ż����λ */
typedef enum
{
    NO_PARITY = 0,          // ��У��λ
    EVEN_PARITY,            // żУ�飬��֤1�ĸ�����ż����
    ODD_PARITY              // ��У��
}Parities;


/* ���� */
typedef enum
{
    NO_FLOW_CTRL = 0,
    RTS_FLOW_CTRL,
    CTS_FLOW_CTRL,
    RTS_CTS_FLOW_CTRL
}FlowCtrls;


/* �ж�״̬ */
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