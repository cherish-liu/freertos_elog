#ifndef _LED_WATCHDOG_H_
#define _LED_WATCHDOG_H_

// LED������
#define GPIO_BOARD_WORK_STATUS_LED  PC_1    /* ���ӹ���״ָ̬ʾ�ƣ�ƽʱ�������������� */
#define GPIO_BOARD_WORK_MODE_LED    PC_2    /* ���ӹ���ģʽָʾ�ƣ�����ʱ������������ */
#define GPIO_RESERVE_LED            PD_2    /* ���õƣ��͵�ƽ�� */

// ���Ź�����
#define GPIO_WATCHDOG       PA_0


void BoardWorkStatusLedInit(void);

void BoardWorkStatusLedOn(void);

void BoardWorkStatusLedOff(void);

void BoardWorkStatusLedToggle(void);

void BoardWorkModeLedInit(void);

void BoardDebugLedOn(void);

void BoardDebugLedOff(void);

void ReserveLedInit(void);

void ReserveLedOn(void);

void ReserveLedOff(void);

void WatchDogInit(void);

void FeedWatchDog(void);

#endif  /* led_watchdog.h */