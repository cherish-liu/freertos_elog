#include <stdio.h>

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"

#include "intrinsics.h"
#include "gpio.h"


/*!
 *  功  能: GPIOA-E 寄存器恢复默认值
 *  参  数: 没有参数
 *  retval: 无返回值
 *  
 *  注  意: 该函数在GPIO初始化之前调用，且全工程只能调用一次
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
 *  功  能: GPIO的初始化
 *  param1: 要初始化的GPIO结构体，在 gpio.h 中定义
 *  param2: 使用的引脚号 PA_0、PA_1、等等，在 pinNane_boad.h 中定义
 *  param3: 引脚模式，在 gpio.h 中定义
 *  param4: 初始值，只能是 0 或 1
 *  retval: 无返回值 
 *
 *  注  意: 只有引脚模式设置为推挽输出，参数4即初始值设定才有效
 *  注  意: 在配置GPIO之前需要先调用一次 GpioDeInit() 函数，全工程只调用一次
 */
void GpioInit( Gpio_t *obj, PinNames pin, PinModes mode, uint8_t value )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    obj->pinName = pin;

    if( pin == NC )
    {
        return;
    }

    obj->pinIndex = ( 0x01 << ( obj->pinName & 0x0F ) );    // 0x0001、0x0002、0x0004、0x0008...等等

    // 使能时钟
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
    
    GPIO_InitStructure.GPIO_Pin =  obj->pinIndex ;      // 引脚号
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
 
    // 模式选择
    if( mode == PIN_Mode_AIN )              // 模拟输入               
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    }   
    else if( mode == PIN_Mode_IN_FLOATING )// 浮空输入    
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if( mode == PIN_Mode_IPD )         // 下拉输入
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if( mode == PIN_Mode_IPU )         // 上拉输入
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if( mode == PIN_Mode_Out_OD )      // 开漏输出
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    }
    else if( mode == PIN_Mode_Out_PP )      // 推挽输出
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if( mode == PIN_Mode_AF_OD )       // 复用开漏输出
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    }
    else if( mode == PIN_Mode_AF_PP )       // 复用推挽输出
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    }

    GPIO_Init(obj->port, &GPIO_InitStructure); // GPIO初始化
    
    if( mode == PIN_Mode_Out_PP )
    {
        if(value == 0)
            GPIO_WriteBit( obj->port, obj->pinIndex, Bit_RESET );
        else if(value == 1)
            GPIO_WriteBit( obj->port, obj->pinIndex, Bit_SET );
    }
}


/*!
 *  功  能: GPIO设置
 *  param1: 要设置的GPIO对象，在 gpio.h 中定义
 *  param2: 设置的值
 *  retval: 无返回值 
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
 *  功  能: GPIO读取输入值
 *  param1: 要读取的GPIO对象，在 gpio.h 中定义
 *  retval: 读取到的值，返回 0 或 1 
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
 *  功  能: 切换翻转 GPIO 引脚的输出电平值
 *  param1: 要操作的GPIO对象，在 gpio.h 中定义
 *  retval: 无返回值
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
 *  功  能: 切换翻转 GPIO 引脚的输出电平值
 *  param1: 要操作的GPIO对象，在 gpio.h 中定义
 *  retval: 无返回值
 *
 *  注  意: 中断优先级分组全工程只能设置一次，在中断配置前调用
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
 *  功  能: 所有的外部中断线 寄存器恢复默认值
 *  参  数: 没有参数
 *  retval: 无返回值
 *  
 *  注  意: 该函数在外部中断配置之前调用，且全工程只能调用一次
 */
void ExtiDeInit(void)
{
    EXTI_DeInit();
}


/*!
 *  功  能: GPIO的中断配置
 *  param1: 要配置的 GPIO 对象，在 gpio.h 中定义
 *  param2: 抢占优先级，注意与中断优先级分组相对应
 *  param3: 子优先级，注意与中断优先级分组相对应
 *  param4: 中断的触发方式，可选上升沿触发、下降沿触发和双边触发
 *  retval: 无返回值 
 *
 *  注  意: 中断优先级分组在 main.c 一开始定义，全工程只定义一次
 */
void GpioSetInterrupt( Gpio_t *obj, uint8_t preemptionPriority, uint8_t subPriority, IrqModes irqMode)
{
    NVIC_InitTypeDef NVIC_InitStructure;    // 配置嵌套向量中断控制器NVIC
    EXTI_InitTypeDef EXTI_InitStructure;    // 外部中断
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // 选择用作 EXTI Line 的 GPIO 引脚
    if(obj->port == GPIOA)
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, (obj->pinName)&0x0F );    // 将中断线与GPIO联系起来 GPIO_PinSourcex 值为 0x00-0x0F
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
    
    
    // 配置嵌套向量中断控制器NVIC
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             // 使能中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;                // 子优先级
    
    if(obj->pinIndex == GPIO_Pin_0)
    {
        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;        // 配置中断源
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
    
    NVIC_Init(&NVIC_InitStructure);     // 嵌套向量中断控制器初始化
    
    
    // 外部中断
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
   
    // 中断的触发方式
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
    
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // 使能中断
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // EXTI为中断模式
    
    EXTI_Init(&EXTI_InitStructure);
}


/*!
 *  功  能: 获取外部中断的状态
 *  param1: 要获取外部中断的GPIO对象
 *  retval: RESET = 0, SET = !RESET 
 *
 *  注  意: 本函数只包含了外部中断0-15的状态获取，对于RTC和USB等16-19的中断需要自己定义
 */
ITStatus ExtiGetIntStatus(Gpio_t *obj)
{
    // obj->pinIndex 的值为 uint16_t  0x0001、 0x0002、 0x0004、 0x0008等   例如：GPIO_Pin_0
    // 外部中断线定义的值为 uint32_t 0x00001、0x00002、0x00004、0x00008等  例如：EXTI_Line0
    // 此处为了节省代码直接用了 obj->pinIndex 的值
    return EXTI_GetITStatus( (uint32_t)obj->pinIndex ); 
}


/*!
 *  功  能: 清除外部中断标志位
 *  param1: 要清除外部中断的GPIO对象
 *  retval: 无返回值 
 *
 *  注  意: 本函数只包含了外部中断0-15的状态获取，对于RTC和USB等16-19的中断需要自己定义
 */
void ExtiClearIntFlag(Gpio_t *obj)
{
    EXTI_ClearITPendingBit( (uint32_t)obj->pinIndex );  // EXTI_Line0   0x01; 0x02; 0x04; 0x08; 0x10 等等
}


/*!
 *  功  能: 使能某个 GPIO 的外部中断（使能来自线x上的中断请求）
 *  param1: 要操作的GPIO对象
 *  retval: 无返回值 
 *
 *  注  意: 本工程将设置中断模式为外部中断，而不是事件
 *          外部中断屏蔽寄存器(EXTI_IMR)  0为屏蔽外部中断，1为使能外部中断 
 */
void ExtiIntEnable(Gpio_t *obj)
{
    EXTI->IMR |= (obj->pinIndex);   // 0x01、      0x02、      0x04、      0x08 ...      等
                                    // EXTI_Line0、EXTI_Line1、EXTI_Line2、EXTI_Line3 ...等
}


/*!
 *  功  能: 禁止某个 GPIO 的外部中断（禁止来自线x上的中断请求）
 *  param1: 要操作的GPIO对象
 *  retval: 无返回值 
 *
 *  注  意: 本工程将设置中断模式为外部中断，而不是事件
 *          外部中断屏蔽寄存器(EXTI_IMR)  0为屏蔽外部中断，1为使能外部中断 
 */
void ExtiIntDisable(Gpio_t *obj)
{
    EXTI->IMR &= ~(obj->pinIndex);  // 0x01、      0x02、      0x04、      0x08 ...      等 
                                    // EXTI_Line0、EXTI_Line1、EXTI_Line2、EXTI_Line3 ...等
}


/*!
 *  功  能: 关闭全局中断
 *  param1: 无
 *  retval: 无
 */
void BoardDisableIrq(void)
{
    __disable_interrupt();
}


/*!
 *  功  能: 使能全局中断
 *  param1: 无
 *  retval: 无
 */
void BoardEnableIrq(void)
{
    __enable_interrupt();
}

















