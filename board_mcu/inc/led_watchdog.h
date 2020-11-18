#ifndef _LED_WATCHDOG_H_
#define _LED_WATCHDOG_H_

// LED灯引脚
#define GPIO_BOARD_WORK_STATUS_LED  PC_1    /* 板子工作状态指示灯，平时闪亮，升级常亮 */
#define GPIO_BOARD_WORK_MODE_LED    PC_2    /* 板子工作模式指示灯，调试时亮，工作不亮 */
#define GPIO_RESERVE_LED            PD_2    /* 备用灯，低电平亮 */

// 看门狗引脚
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