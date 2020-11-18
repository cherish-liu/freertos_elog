#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f10x.h"
#include "pinName_board.h"
#include <stdint.h>

/* ���Ŷ��� */
typedef enum
{
    MCU_PINS,
    NC = (int)0xFFFFFFFF    // Not connected
}PinNames;

typedef struct
{
    PinNames pinName;       // 
    uint16_t pinIndex;  // GPIO_Pin_x, xȡֵΪ0-15, 0x0001��0x0002��0x0004��0x0008...�ȵ�
    void *port;
}Gpio_t;

typedef enum
{
    PIN_Mode_AIN = 0,       // ģ������
    PIN_Mode_IN_FLOATING,   // ��������
    PIN_Mode_IPD,           // ��������
    PIN_Mode_IPU,           // ��������
    PIN_Mode_Out_OD,        // ��©���
    PIN_Mode_Out_PP,        // �������
    PIN_Mode_AF_OD,         // ���ÿ�©���
    PIN_Mode_AF_PP          // �����������
}PinModes;

typedef enum
{
    PIN_NO_PULL = 0,
    PIN_PULL_UP,
    PIN_PULL_DOWN
}PinTypes;

typedef enum
{
    PIN_PUSH_PULL = 0,
    PIN_OPEN_DRAIN
}PinConfigs;

typedef enum
{
    IRQ_RISING_EDGE = 0,
    IRQ_FALLING_EDGE,
    IRQ_RISING_FALLING_EDGE
}IrqModes;

typedef enum
{
    NVIC_PRIORITY_GROUP_0 = 0,
    NVIC_PRIORITY_GROUP_1,
    NVIC_PRIORITY_GROUP_2,
    NVIC_PRIORITY_GROUP_3,
    NVIC_PRIORITY_GROUP_4
}NvicPriorityGroups;

 
// GPIO ���    
void GpioDeInit(void);

void GpioInit( Gpio_t *obj, PinNames pinName, PinModes mode, uint8_t value );

void GpioWrite( Gpio_t *obj, uint8_t value );

uint8_t GpioRead( Gpio_t *obj );

void GpioToggle(Gpio_t *obj);

    
// �ⲿ�ж����    
void SetNvicPriorityGroup( NvicPriorityGroups group );

void ExtiDeInit(void);
    
void GpioSetInterrupt( Gpio_t *obj, uint8_t preemptionPriority, uint8_t subPriority, IrqModes irqMode);        

ITStatus ExtiGetIntStatus(Gpio_t *obj);

void ExtiClearIntFlag(Gpio_t *obj);

void ExtiIntEnable(Gpio_t *obj);

void ExtiIntDisable(Gpio_t *obj);


// ȫ���ж����
void BoardDisableIrq(void);

void BoardEnableIrq(void);


    
#endif  /* gpio.h */