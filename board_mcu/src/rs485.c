#include "rs485.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"

static Rs485_t Rs485_A;        // ����1, 

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
 *  ��  ��: RS485 A�ĳ�ʼ��
 *  param1: ������
 *  retval: �޷���ֵ 
 *
 *  ˵  ��: ����1  8n1
 */
void Rs485_A_Init(void)
{
    GpioInit( &Rs485_A.Rs485_En, RS485_A_EN, PIN_Mode_Out_PP, 0 );  // 485��ʼ��Ϊ����ģʽ
    
    UartInit( &Rs485_A.Rs485_Uart, RS485_A_UART_NUM, RS485_A_TX, RS485_A_RX );
    UartConfig( &Rs485_A.Rs485_Uart, RX_TX, 9600, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL );  //Ĭ�ϲ��� 
    //UartSetInterrupt( &Rs485_A.Rs485_Uart, 0, 0);
}


/*!
 *  ��  ��: RS485_A ʹ�ܷ���
 *  param1: ��
 *  retval: �� 
 */
void Rs485_A_TxEnable(void)
{
    GpioWrite( &Rs485_A.Rs485_En, 1 );  // 1��ʾ����ģʽ
    //Delay_ms(RS485_DELAY_MS);
}


/*!
 *  ��  ��: RS485_A ʹ�ܽ���
 *  param1: ��
 *  retval: �� 
 */
void Rs485_A_RxEnable(void)
{
    GpioWrite( &Rs485_A.Rs485_En, 0 );          // 0��ʾ����ģʽ
    //Rs485_A_ClearIntFlag( PIN_UART_FLAG_RXNE ); // ��������ж�
    //Delay_ms(RS485_DELAY_MS);
}