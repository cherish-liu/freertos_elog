#include "led_watchdog.h"
#include "gpio.h"

/* 定义的外设结构体 */
static Gpio_t boardWorkLed_s;
static Gpio_t workModeLed_s;
static Gpio_t reserveLed_s;
static Gpio_t watchDog_s;


/*!
 *  功  能: 模块工作状态指示灯初始化
 *  param1: 无
 *  retval: 无
 */
void BoardWorkStatusLedInit(void)
{
    GpioInit( &boardWorkLed_s, GPIO_BOARD_WORK_STATUS_LED, PIN_Mode_Out_PP, 0 );    // 低电平点亮
}


/*!
 *  功  能: 模块工作状态指示灯 常亮
 *  param1: 无
 *  retval: 无
 */
void BoardWorkStatusLedOn(void)
{
    GpioWrite(&boardWorkLed_s, 0);
}

/*!
 *  功  能: 模块工作状态指示灯 常亮
 *  param1: 无
 *  retval: 无
 */
void BoardWorkStatusLedOff(void)
{
    GpioWrite(&boardWorkLed_s, 1);
}


/*!
 *  功  能: 模块工作状态指示灯翻转
 *  param1: 无
 *  retval: 无
 */
void BoardWorkStatusLedToggle(void)
{
    GpioToggle(&boardWorkLed_s);
}



/*!
 *  功  能: 模块工作模式指示灯初始化，调试模式和工程模式
 *  param1: 无
 *  retval: 无
 */
void BoardWorkModeLedInit(void)
{
    GpioInit( &workModeLed_s, GPIO_BOARD_WORK_MODE_LED, PIN_Mode_Out_PP, 1 );    // 低电平点亮
}


/*!
 *  功  能: 模块调试指示灯 亮
 *  param1: 无
 *  retval: 无
 */
void BoardDebugLedOn(void)
{
    GpioWrite(&workModeLed_s, 0);
}

/*!
 *  功  能: 模块调试指示灯 灭
 *  param1: 无
 *  retval: 无
 */
void BoardDebugLedOff(void)
{
    GpioWrite(&workModeLed_s, 1);
}


/*!
 *  功  能: 备用灯初始化
 *  param1: 无
 *  retval: 无
 */
void ReserveLedInit(void)
{
    GpioInit( &reserveLed_s, GPIO_RESERVE_LED, PIN_Mode_Out_PP, 1 );    // 低电平点亮
}


/*!
 *  功  能: 备用灯亮
 *  param1: 无
 *  retval: 无
 */
void ReserveLedOn(void)
{
    GpioWrite(&reserveLed_s, 0);
}


/*!
 *  功  能: 备用灯灭
 *  param1: 无
 *  retval: 无
 */
void ReserveLedOff(void)
{
    GpioWrite(&reserveLed_s, 1);
}



/*!
 *  功  能: 硬件看门狗 初始化 
 *  param1: 无
 *  retval: 无
 *
 *  说  明: SP706SEN-L/TR 硬件看门狗，反转WDI引脚的电平状态可喂狗，喂狗间隔应 <1.6s（可靠时间间隔应该小于1s）
 */
void WatchDogInit(void)
{
    GpioInit( &watchDog_s, GPIO_WATCHDOG, PIN_Mode_Out_PP, 1 );    // 低电平点亮
}


/*!
 *  功  能: 看门狗喂狗函数
 *  param1: 无
 *  retval: 无
 */
void FeedWatchDog(void)
{
    GpioToggle(&watchDog_s);
}