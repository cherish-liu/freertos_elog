#include "led_watchdog.h"
#include "gpio.h"

/* ���������ṹ�� */
static Gpio_t boardWorkLed_s;
static Gpio_t workModeLed_s;
static Gpio_t reserveLed_s;
static Gpio_t watchDog_s;


/*!
 *  ��  ��: ģ�鹤��״ָ̬ʾ�Ƴ�ʼ��
 *  param1: ��
 *  retval: ��
 */
void BoardWorkStatusLedInit(void)
{
    GpioInit( &boardWorkLed_s, GPIO_BOARD_WORK_STATUS_LED, PIN_Mode_Out_PP, 0 );    // �͵�ƽ����
}


/*!
 *  ��  ��: ģ�鹤��״ָ̬ʾ�� ����
 *  param1: ��
 *  retval: ��
 */
void BoardWorkStatusLedOn(void)
{
    GpioWrite(&boardWorkLed_s, 0);
}

/*!
 *  ��  ��: ģ�鹤��״ָ̬ʾ�� ����
 *  param1: ��
 *  retval: ��
 */
void BoardWorkStatusLedOff(void)
{
    GpioWrite(&boardWorkLed_s, 1);
}


/*!
 *  ��  ��: ģ�鹤��״ָ̬ʾ�Ʒ�ת
 *  param1: ��
 *  retval: ��
 */
void BoardWorkStatusLedToggle(void)
{
    GpioToggle(&boardWorkLed_s);
}



/*!
 *  ��  ��: ģ�鹤��ģʽָʾ�Ƴ�ʼ��������ģʽ�͹���ģʽ
 *  param1: ��
 *  retval: ��
 */
void BoardWorkModeLedInit(void)
{
    GpioInit( &workModeLed_s, GPIO_BOARD_WORK_MODE_LED, PIN_Mode_Out_PP, 1 );    // �͵�ƽ����
}


/*!
 *  ��  ��: ģ�����ָʾ�� ��
 *  param1: ��
 *  retval: ��
 */
void BoardDebugLedOn(void)
{
    GpioWrite(&workModeLed_s, 0);
}

/*!
 *  ��  ��: ģ�����ָʾ�� ��
 *  param1: ��
 *  retval: ��
 */
void BoardDebugLedOff(void)
{
    GpioWrite(&workModeLed_s, 1);
}


/*!
 *  ��  ��: ���õƳ�ʼ��
 *  param1: ��
 *  retval: ��
 */
void ReserveLedInit(void)
{
    GpioInit( &reserveLed_s, GPIO_RESERVE_LED, PIN_Mode_Out_PP, 1 );    // �͵�ƽ����
}


/*!
 *  ��  ��: ���õ���
 *  param1: ��
 *  retval: ��
 */
void ReserveLedOn(void)
{
    GpioWrite(&reserveLed_s, 0);
}


/*!
 *  ��  ��: ���õ���
 *  param1: ��
 *  retval: ��
 */
void ReserveLedOff(void)
{
    GpioWrite(&reserveLed_s, 1);
}



/*!
 *  ��  ��: Ӳ�����Ź� ��ʼ�� 
 *  param1: ��
 *  retval: ��
 *
 *  ˵  ��: SP706SEN-L/TR Ӳ�����Ź�����תWDI���ŵĵ�ƽ״̬��ι����ι�����Ӧ <1.6s���ɿ�ʱ����Ӧ��С��1s��
 */
void WatchDogInit(void)
{
    GpioInit( &watchDog_s, GPIO_WATCHDOG, PIN_Mode_Out_PP, 1 );    // �͵�ƽ����
}


/*!
 *  ��  ��: ���Ź�ι������
 *  param1: ��
 *  retval: ��
 */
void FeedWatchDog(void)
{
    GpioToggle(&watchDog_s);
}