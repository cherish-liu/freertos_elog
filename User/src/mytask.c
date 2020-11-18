#include "FreeRTOS.h"
#include "task.h"

#include "led_watchdog.h"

#include "mytask.h"


#define LOG_TAG "mytask"
#include "elog.h"

static TaskHandle_t ledTask_Handle = NULL;

/* 为了方便管理，所有的任务创建函数都放在这个函数里面 */
void CreateTask(void)
{
    BaseType_t ret;

    ret = xTaskCreate((TaskFunction_t )ledTask,          /* 任务入口函数 */
                      (const char* )"ledTask",           /* 任务名字 */
                      (uint16_t )512,                    /* 任务栈大小 */
                      (void* )NULL,                      /* 任务入口函数参数 */
                      (UBaseType_t )1,                   /* 任务的优先级 */
                      (TaskHandle_t* )&ledTask_Handle);  /* 任务控制块指针 */
    
    if (pdPASS != ret)
        return;
    
    vTaskStartScheduler(); /* 启动任务，开启调度 */
}

/* led 任务 */
void ledTask(void* param)
{
    while(1)
    {
        ReserveLedOn();
        vTaskDelay(500); 
        ReserveLedOff();
        vTaskDelay(500); 
        log_a("Hello EasyLogger!");
    }
}