#ifndef _RS485_H_
#define _RS485_H_

#include "gpio.h"
#include "uart.h"

#define RS485_RECV_MAX_LEN      (32)

extern uint8_t rs485_A_RecvData[RS485_RECV_MAX_LEN];
extern uint8_t rs485_A_RecvCnt;
extern uint8_t rs485_A_RecvFlag;

extern uint8_t rs485_B_RecvData[RS485_RECV_MAX_LEN];
extern uint8_t rs485_B_RecvCnt;
extern uint8_t rs485_B_RecvFlag;

extern uint8_t rs485_A_SendData[RS485_RECV_MAX_LEN];
extern uint8_t rs485_A_SendFlag;
extern uint8_t rs485_A_SendCnt;

/* RS485结构体 */
typedef struct
{
    Uart_t Rs485_Uart;
    Gpio_t Rs485_En;  // 1 表示发送模式，0表示接收模式
}Rs485_t;


// RS485_A  串口1 
#define RS485_A_UART_NUM    UART_1
#define RS485_A_TX          PA_9
#define RS485_A_RX          PA_10
#define RS485_A_EN          PD_1
    
// RS485_B  串口4 
#define RS485_B_UART_NUM    UART_4
#define RS485_B_TX          PC_10
#define RS485_B_RX          PC_11
#define RS485_B_EN          PD_0

//InterfaceParaSet参数
#define ParaSet_485A        (0)
#define ParaSet_MBUS        (1)
#define ParaSet_485B        (2)

#define RS485_DELAY_MS      (5)

void Rs485_A_Init(void);

void Rs485_B_Init(void);

uint8_t InterfaceParaSet(uint8_t Port,uint8_t Para);

void Rs485_A_TxEnable(void);

void Rs485_A_RxEnable(void);

void Rs485_B_TxEnable(void);

void Rs485_B_RxEnable(void);

void Rs485_A_SendString(uint8_t *str);

void Rs485_A_SendArray(uint8_t *array, uint8_t len);

void Rs485_B_SendString(uint8_t *str);

void Rs485_B_SendArray(uint8_t *array, uint8_t len);

uint16_t Rs485_A_RecvData(void);

uint16_t Rs485_B_RecvData(void);

ITStatus Rs485_A_GetIntStatus(UartIntStatuses intStatus);

ITStatus Rs485_B_GetIntStatus(UartIntStatuses intStatus);

void Rs485_A_ClearIntFlag(UartIntStatuses uartFlag);

void Rs485_B_ClearIntFlag(UartIntStatuses uartFlag);

uint16_t UartRecvDataPreprocessing(Uart_t *obj);

void Rs485_A_DmaInit(void);


#endif  /* rs485.h */