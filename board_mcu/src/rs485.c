#include "rs485.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"

static Rs485_t Rs485_A;        // 串口1, 

uint8_t rs485_A_RecvData[RS485_RECV_MAX_LEN] = {0};
uint8_t rs485_A_RecvCnt = 0;
uint8_t rs485_A_RecvFlag = 0;

uint8_t rs485_B_RecvData[RS485_RECV_MAX_LEN] = {0};
uint8_t rs485_B_RecvCnt = 0;
uint8_t rs485_B_RecvFlag = 0;


uint8_t rs485_A_SendData[RS485_RECV_MAX_LEN] = {0};
uint8_t rs485_A_SendFlag = 0;
uint8_t rs485_A_SendCnt = 0;

/*!
 *  功  能: RS485 A的初始化
 *  param1: 波特率
 *  retval: 无返回值 
 *
 *  说  明: 串口1  8n1
 */
void Rs485_A_Init(void)
{
    GpioInit( &Rs485_A.Rs485_En, RS485_A_EN, PIN_Mode_Out_PP, 0 );  // 485初始化为接收模式
    
    UartInit( &Rs485_A.Rs485_Uart, RS485_A_UART_NUM, RS485_A_TX, RS485_A_RX );
    UartConfig( &Rs485_A.Rs485_Uart, RX_TX, 9600, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL );  //默认参数 
    //UartSetInterrupt( &Rs485_A.Rs485_Uart, 0, 0);
}


/*!
 *  功  能: RS485_A 使能发送
 *  param1: 无
 *  retval: 无 
 */
void Rs485_A_TxEnable(void)
{
    GpioWrite( &Rs485_A.Rs485_En, 1 );  // 1表示发送模式
    //Delay_ms(RS485_DELAY_MS);
}


/*!
 *  功  能: RS485_A 使能接收
 *  param1: 无
 *  retval: 无 
 */
void Rs485_A_RxEnable(void)
{
    GpioWrite( &Rs485_A.Rs485_En, 0 );          // 0表示接收模式
    //Rs485_A_ClearIntFlag( PIN_UART_FLAG_RXNE ); // 清除接收中断
    //Delay_ms(RS485_DELAY_MS);
}