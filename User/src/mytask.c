#include "FreeRTOS.h"
#include "task.h"

#include "led_watchdog.h"

#include "mytask.h"


#define LOG_TAG "mytask"
#include "elog.h"

static TaskHandle_t ledTask_Handle = NULL;

/* Ϊ�˷���������е����񴴽���������������������� */
void CreateTask(void)
{
    BaseType_t ret;

    ret = xTaskCreate((TaskFunction_t )ledTask,          /* ������ں��� */
                      (const char* )"ledTask",           /* �������� */
                      (uint16_t )512,                    /* ����ջ��С */
                      (void* )NULL,                      /* ������ں������� */
                      (UBaseType_t )1,                   /* ��������ȼ� */
                      (TaskHandle_t* )&ledTask_Handle);  /* ������ƿ�ָ�� */
    
    if (pdPASS != ret)
        return;
    
    vTaskStartScheduler(); /* �������񣬿������� */
}

/* led ���� */
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