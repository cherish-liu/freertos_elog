#include <stdio.h>

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"

#include "intrinsics.h"
#include "gpio.h"


/*!
 *  ��  ��: GPIOA-E �Ĵ����ָ�Ĭ��ֵ
 *  ��  ��: û�в���
 *  retval: �޷���ֵ
 *  
 *  ע  ��: �ú�����GPIO��ʼ��֮ǰ���ã���ȫ����ֻ�ܵ���һ��
 */
void GpioDeInit(void)
{
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
    GPIO_DeInit(GPIOD);
    GPIO_DeInit(GPIOE);
}


/*!
 *  ��  ��: GPIO�ĳ�ʼ��
 *  param1: Ҫ��ʼ����GPIO�ṹ�壬�� gpio.h �ж���
 *  param2: ʹ�õ����ź� PA_0��PA_1���ȵȣ��� pinNane_boad.h �ж���
 *  param3: ����ģʽ���� gpio.h �ж���
 *  param4: ��ʼֵ��ֻ���� 0 �� 1
 *  retval: �޷���ֵ 
 *
 *  ע  ��: ֻ������ģʽ����Ϊ�������������4����ʼֵ�趨����Ч
 *  ע  ��: ������GPIO֮ǰ��Ҫ�ȵ���һ�� GpioDeInit() ������ȫ����ֻ����һ��
 */
void GpioInit( Gpio_t *obj, PinNames pin, PinModes mode, uint8_t value )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    obj->pinName = pin;

    if( pin == NC )
    {
        return;
    }

    obj->pinIndex = ( 0x01 << ( obj->pinName & 0x0F ) );    // 0x0001��0x0002��0x0004��0x0008...�ȵ�

    // ʹ��ʱ��
    if( ( obj->pinName & 0xF0 ) == 0x00 )   //GPIOA
    {
        obj->port = GPIOA;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if( ( obj->pinName & 0xF0 ) == 0x10 )  // GPIOB
    {
        obj->port = GPIOB;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if( ( obj->pinName & 0xF0 ) == 0x20 )  // GPIOC
    {
        obj->port = GPIOC;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    else if( ( obj->pinName & 0xF0 ) == 0x30 )  // GPIOD
    {
        obj->port = GPIOD;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }
    else if( ( obj->pinName & 0xF0 ) == 0x40 )  // GPIOE
    {
        obj->port = GPIOE;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }
    
    GPIO_InitStructure.GPIO_Pin =  obj->pinIndex ;      // ���ź�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
 
    // ģʽѡ��
    if( mode == PIN_Mode_AIN )              // ģ������               
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    }   
    else if( mode == PIN_Mode_IN_FLOATING )// ��������    
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if( mode == PIN_Mode_IPD )         // ��������
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if( mode == PIN_Mode_IPU )         // ��������
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if( mode == PIN_Mode_Out_OD )      // ��©���
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    }
    else if( mode == PIN_Mode_Out_PP )      // �������
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if( mode == PIN_Mode_AF_OD )       // ���ÿ�©���
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    }
    else if( mode == PIN_Mode_AF_PP )       // �����������
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    }

    GPIO_Init(obj->port, &GPIO_InitStructure); // GPIO��ʼ��
    
    if( mode == PIN_Mode_Out_PP )
    {
        if(value == 0)
            GPIO_WriteBit( obj->port, obj->pinIndex, Bit_RESET );
        else if(value == 1)
            GPIO_WriteBit( obj->port, obj->pinIndex, Bit_SET );
    }
}


/*!
 *  ��  ��: GPIO����
 *  param1: Ҫ���õ�GPIO������ gpio.h �ж���
 *  param2: ���õ�ֵ
 *  retval: �޷���ֵ 
 */
void GpioWrite( Gpio_t *obj, uint8_t value )
{
    if( ( obj == NULL ) || ( obj->port == NULL ) )
    {
        return;
    }
    // Check if pinName is not connected
    if( obj->pinName == NC )
    {
        return;
    }
    
    if(value == 0)
        GPIO_WriteBit( obj->port, obj->pinIndex, Bit_RESET );
    else if(value == 1)
        GPIO_WriteBit( obj->port, obj->pinIndex, Bit_SET );
}


/*!
 *  ��  ��: GPIO��ȡ����ֵ
 *  param1: Ҫ��ȡ��GPIO������ gpio.h �ж���
 *  retval: ��ȡ����ֵ������ 0 �� 1 
 */
uint8_t GpioRead( Gpio_t *obj )
{
    if( obj == NULL )
    {
        return 0;
    }

    if( obj->pinName == NC )
    {
        return 0;
    }
    
    return GPIO_ReadInputDataBit( obj->port, obj->pinIndex );
}


/*!
 *  ��  ��: �л���ת GPIO ���ŵ������ƽֵ
 *  param1: Ҫ������GPIO������ gpio.h �ж���
 *  retval: �޷���ֵ
 */
void GpioToggle(Gpio_t *obj)
{
    uint8_t value;
    
    value = GPIO_ReadOutputDataBit(obj->port, obj->pinIndex);
    
    if(value == 0)
        GpioWrite( obj, 1 );
    else
        GpioWrite( obj, 0 );
}


/*!
 *  ��  ��: �л���ת GPIO ���ŵ������ƽֵ
 *  param1: Ҫ������GPIO������ gpio.h �ж���
 *  retval: �޷���ֵ
 *
 *  ע  ��: �ж����ȼ�����ȫ����ֻ������һ�Σ����ж�����ǰ����
 */
void SetNvicPriorityGroup( NvicPriorityGroups group )
{
    switch(group)
    {
    case NVIC_PRIORITY_GROUP_0:
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
        break;
    case NVIC_PRIORITY_GROUP_1:
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
        break;
    case NVIC_PRIORITY_GROUP_2:
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        break;
    case NVIC_PRIORITY_GROUP_3:
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
        break;
    case NVIC_PRIORITY_GROUP_4:
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
        break;
    default:
        break;
    }
}


/*!
 *  ��  ��: ���е��ⲿ�ж��� �Ĵ����ָ�Ĭ��ֵ
 *  ��  ��: û�в���
 *  retval: �޷���ֵ
 *  
 *  ע  ��: �ú������ⲿ�ж�����֮ǰ���ã���ȫ����ֻ�ܵ���һ��
 */
void ExtiDeInit(void)
{
    EXTI_DeInit();
}


/*!
 *  ��  ��: GPIO���ж�����
 *  param1: Ҫ���õ� GPIO ������ gpio.h �ж���
 *  param2: ��ռ���ȼ���ע�����ж����ȼ��������Ӧ
 *  param3: �����ȼ���ע�����ж����ȼ��������Ӧ
 *  param4: �жϵĴ�����ʽ����ѡ�����ش������½��ش�����˫�ߴ���
 *  retval: �޷���ֵ 
 *
 *  ע  ��: �ж����ȼ������� main.c һ��ʼ���壬ȫ����ֻ����һ��
 */
void GpioSetInterrupt( Gpio_t *obj, uint8_t preemptionPriority, uint8_t subPriority, IrqModes irqMode)
{
    NVIC_InitTypeDef NVIC_InitStructure;    // ����Ƕ�������жϿ�����NVIC
    EXTI_InitTypeDef EXTI_InitStructure;    // �ⲿ�ж�
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // ѡ������ EXTI Line �� GPIO ����
    if(obj->port == GPIOA)
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, (obj->pinName)&0x0F );    // ���ж�����GPIO��ϵ���� GPIO_PinSourcex ֵΪ 0x00-0x0F
    }
    else if(obj->port == GPIOB)
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, (obj->pinName)&0x0F );    // GPIO_PinSource0 -> 0x00; 0x01; 0x02; 0x03; 0x04; ... 0x0F
    }
    else if(obj->port == GPIOC)
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, (obj->pinName)&0x0F );
    }
    else if(obj->port == GPIOD)
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, (obj->pinName)&0x0F );
    }
    else if(obj->port == GPIOE)
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, (obj->pinName)&0x0F );
    }
    
    
    // ����Ƕ�������жϿ�����NVIC
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             // ʹ���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;                // �����ȼ�
    
    if(obj->pinIndex == GPIO_Pin_0)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;        // �����ж�Դ
    }
    else if(obj->pinIndex == GPIO_Pin_1)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    }
    else if(obj->pinIndex == GPIO_Pin_2)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    }
    else if(obj->pinIndex == GPIO_Pin_3)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    }
    else if(obj->pinIndex == GPIO_Pin_4)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    }
    else if(obj->pinIndex==GPIO_Pin_5 || obj->pinIndex==GPIO_Pin_6 || obj->pinIndex==GPIO_Pin_7 || obj->pinIndex==GPIO_Pin_8 || obj->pinIndex==GPIO_Pin_9)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    }
    else if(obj->pinIndex==GPIO_Pin_10 || obj->pinIndex==GPIO_Pin_11 || obj->pinIndex==GPIO_Pin_12 || obj->pinIndex==GPIO_Pin_13 || obj->pinIndex==GPIO_Pin_14 || obj->pinIndex==GPIO_Pin_15)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    }
    
    NVIC_Init(&NVIC_InitStructure);     // Ƕ�������жϿ�������ʼ��
    
    
    // �ⲿ�ж�
    switch(obj->pinIndex)
    {
    case GPIO_Pin_0:
        EXTI_InitStructure.EXTI_Line = EXTI_Line0;   break;
    case GPIO_Pin_1:
        EXTI_InitStructure.EXTI_Line = EXTI_Line1;   break;
    case GPIO_Pin_2:
        EXTI_InitStructure.EXTI_Line = EXTI_Line2;   break;
    case GPIO_Pin_3:
        EXTI_InitStructure.EXTI_Line = EXTI_Line3;   break;
    case GPIO_Pin_4:
        EXTI_InitStructure.EXTI_Line = EXTI_Line4;   break;
    case GPIO_Pin_5:
        EXTI_InitStructure.EXTI_Line = EXTI_Line5;   break;
    case GPIO_Pin_6:
        EXTI_InitStructure.EXTI_Line = EXTI_Line6;   break;
    case GPIO_Pin_7:
        EXTI_InitStructure.EXTI_Line = EXTI_Line7;   break;
    case GPIO_Pin_8:
        EXTI_InitStructure.EXTI_Line = EXTI_Line8;   break;
    case GPIO_Pin_9:
        EXTI_InitStructure.EXTI_Line = EXTI_Line9;   break;
    case GPIO_Pin_10:
        EXTI_InitStructure.EXTI_Line = EXTI_Line10;  break;
    case GPIO_Pin_11:
        EXTI_InitStructure.EXTI_Line = EXTI_Line11;  break;
    case GPIO_Pin_12:
        EXTI_InitStructure.EXTI_Line = EXTI_Line12;  break;
    case GPIO_Pin_13:
        EXTI_InitStructure.EXTI_Line = EXTI_Line13;  break;
    case GPIO_Pin_14:
        EXTI_InitStructure.EXTI_Line = EXTI_Line14;  break;
    case GPIO_Pin_15:
        EXTI_InitStructure.EXTI_Line = EXTI_Line15;  break; 
    default:
        break;
    }
   
    // �жϵĴ�����ʽ
    if(irqMode == IRQ_RISING_EDGE)
    {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    }
    else if(irqMode == IRQ_FALLING_EDGE)
    {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    }
    else if(irqMode == IRQ_RISING_FALLING_EDGE)
    {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    }
    
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // ʹ���ж�
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // EXTIΪ�ж�ģʽ
    
    EXTI_Init(&EXTI_InitStructure);
}


/*!
 *  ��  ��: ��ȡ�ⲿ�жϵ�״̬
 *  param1: Ҫ��ȡ�ⲿ�жϵ�GPIO����
 *  retval: RESET = 0, SET = !RESET 
 *
 *  ע  ��: ������ֻ�������ⲿ�ж�0-15��״̬��ȡ������RTC��USB��16-19���ж���Ҫ�Լ�����
 */
ITStatus ExtiGetIntStatus(Gpio_t *obj)
{
    // obj->pinIndex ��ֵΪ uint16_t  0x0001�� 0x0002�� 0x0004�� 0x0008��   ���磺GPIO_Pin_0
    // �ⲿ�ж��߶����ֵΪ uint32_t 0x00001��0x00002��0x00004��0x00008��  ���磺EXTI_Line0
    // �˴�Ϊ�˽�ʡ����ֱ������ obj->pinIndex ��ֵ
    return EXTI_GetITStatus( (uint32_t)obj->pinIndex ); 
}


/*!
 *  ��  ��: ����ⲿ�жϱ�־λ
 *  param1: Ҫ����ⲿ�жϵ�GPIO����
 *  retval: �޷���ֵ 
 *
 *  ע  ��: ������ֻ�������ⲿ�ж�0-15��״̬��ȡ������RTC��USB��16-19���ж���Ҫ�Լ�����
 */
void ExtiClearIntFlag(Gpio_t *obj)
{
    EXTI_ClearITPendingBit( (uint32_t)obj->pinIndex );  // EXTI_Line0   0x01; 0x02; 0x04; 0x08; 0x10 �ȵ�
}


/*!
 *  ��  ��: ʹ��ĳ�� GPIO ���ⲿ�жϣ�ʹ��������x�ϵ��ж�����
 *  param1: Ҫ������GPIO����
 *  retval: �޷���ֵ 
 *
 *  ע  ��: �����̽������ж�ģʽΪ�ⲿ�жϣ��������¼�
 *          �ⲿ�ж����μĴ���(EXTI_IMR)  0Ϊ�����ⲿ�жϣ�1Ϊʹ���ⲿ�ж� 
 */
void ExtiIntEnable(Gpio_t *obj)
{
    EXTI->IMR |= (obj->pinIndex);   // 0x01��      0x02��      0x04��      0x08 ...      ��
                                    // EXTI_Line0��EXTI_Line1��EXTI_Line2��EXTI_Line3 ...��
}


/*!
 *  ��  ��: ��ֹĳ�� GPIO ���ⲿ�жϣ���ֹ������x�ϵ��ж�����
 *  param1: Ҫ������GPIO����
 *  retval: �޷���ֵ 
 *
 *  ע  ��: �����̽������ж�ģʽΪ�ⲿ�жϣ��������¼�
 *          �ⲿ�ж����μĴ���(EXTI_IMR)  0Ϊ�����ⲿ�жϣ�1Ϊʹ���ⲿ�ж� 
 */
void ExtiIntDisable(Gpio_t *obj)
{
    EXTI->IMR &= ~(obj->pinIndex);  // 0x01��      0x02��      0x04��      0x08 ...      �� 
                                    // EXTI_Line0��EXTI_Line1��EXTI_Line2��EXTI_Line3 ...��
}


/*!
 *  ��  ��: �ر�ȫ���ж�
 *  param1: ��
 *  retval: ��
 */
void BoardDisableIrq(void)
{
    __disable_interrupt();
}


/*!
 *  ��  ��: ʹ��ȫ���ж�
 *  param1: ��
 *  retval: ��
 */
void BoardEnableIrq(void)
{
    __enable_interrupt();
}

















