/*!
 *  定时器相关  
 *  STM32F103xx  定时器2-7  --> APB1总线上 --> 72MHz
 *               定时器1和8 --> APB2总线上 --> 72MHz  
 */

#include <stdio.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include "timer.h"

/*!
 *  功  能: 恢复基本定时器 6 和 7 的寄存器到默认值
 *  param1: 无
 *  retval: 无
 */
void BasicTimerDeInit(void)
{
    TIM_DeInit(TIM6);   // 恢复寄存器到默认值
    TIM_DeInit(TIM7);   // 恢复寄存器到默认值
}
        
/*!
 *  功  能: 基本定时器6 的初始化
 *          基本定时器6 用于产生 200ms 的中断，作为板子工作状态指示灯的定时器（板子工作状态指示灯平时闪亮，升级常亮）
 *  param1: 抢占优先级
 *  param2: 子优先级
 *  retval: 无返回值 
 * 
 *  注  意: 基本定时器包含一个16位自动装载计数器，且只能向上计数
 *          16位可编程(可实时修改)预分频器，用于对输入的时钟按系数为1～65536之间的任意数值分频
 *          基本定时器只有 更新中断，没有捕获/比较中断
 *          基本定时器只适用于大容量的 STM32F101xx 和 STM32F103xx 系列
 */
void BasicTimer6Init(uint8_t preemptionPriority, uint8_t subPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    // 配置嵌套向量中断控制器NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; // 中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;	            // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);     // 嵌套向量中断控制器初始化
    
    
    // 基本定时器的配置
    TIM_DeInit(TIM6);   // 恢复寄存器到默认值
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);    // 使能时钟
    TIM_TimeBaseStructure.TIM_Period = 2000-1;              // 自动重装寄存器的值，从0开始计数
    TIM_TimeBaseStructure.TIM_Prescaler = 7100;             // 计数器的时钟频率CK_CNT等于f CK_PSC /(PSC[15:0]+1)
//    TIM_TimeBaseStructure.TIM_ClockDivision               // 时钟分频因子，基本定时器没有
//    TIM_TimeBaseStructure.TIM_CounterMode                 // 计数器计数模式，基本定时器只能向上计数
//    TIM_TimeBaseStructure.TIM_RepetitionCounter           // 重复计数器的值，基本定时器没有
    
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);     // 初始化 基本定时器6
    
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);               // 清除计数器中断标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);          // 开启计数器中断
    
    TIM_Cmd(TIM6, ENABLE);      // 使能
}    
        

/*!
 *  功  能: 基本定时器7 的初始化，1ms中断一次
 *  param1: 抢占优先级
 *  param2: 子优先级
 *  retval: 无返回值 
 * 
 *  注  意: 基本定时器包含一个16位自动装载计数器，且只能向上计数
 *          16位可编程(可实时修改)预分频器，用于对输入的时钟按系数为1～65536之间的任意数值分频
 *          基本定时器只有 更新中断，没有捕获/比较中断
 *          基本定时器只适用于大容量的 STM32F101xx 和 STM32F103xx 系列
 */
void BasicTimer7Init(uint8_t preemptionPriority, uint8_t subPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    // 配置嵌套向量中断控制器NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;                             // 中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;	            // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);                                             // 嵌套向量中断控制器初始化
    
    
    // 基本定时器7 的配置
    TIM_DeInit(TIM7);   // 恢复寄存器到默认值
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);    // 使能时钟
    TIM_TimeBaseStructure.TIM_Period = 1000-1;             // 自动重装寄存器的值，从0开始计数
    TIM_TimeBaseStructure.TIM_Prescaler = 71;             // 计数器的时钟频率CK_CNT等于f CK_PSC /(PSC[15:0]+1)
//    TIM_TimeBaseStructure.TIM_ClockDivision               // 时钟分频因子，基本定时器没有
//    TIM_TimeBaseStructure.TIM_CounterMode                 // 计数器计数模式，基本定时器只能向上计数
//    TIM_TimeBaseStructure.TIM_RepetitionCounter           // 重复计数器的值，基本定时器没有
    
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);     // 初始化 基本定时器7
    
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);               // 清除计数器中断标志位
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);          // 开启计数器中断
    
    TIM_Cmd(TIM7, ENABLE);      // 使能
    
    BasicTimer7Stop();          // 初始化关闭定时器7
} 


/*!
 *  功  能: 基本定时器6 开始计时
 *  param1: 无
 *  retval: 无返回值
 */
void BasicTimer6Start(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);       // 清除计数器中断标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);  // 开启计数器中断
    
    TIM_Cmd(TIM6, ENABLE);                      // 使能
}


/*!
 *  功  能: 基本定时器7 开始计时
 *  param1: 无
 *  retval: 无返回值
 */
void BasicTimer7Start(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);       // 清除计数器中断标志位
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);  // 开启计数器中断
    
    TIM_Cmd(TIM7, ENABLE);                      // 使能
}


/*!
 *  功  能: 基本定时器6 停止计时
 *  param1: 无
 *  retval: 无返回值
 */
void BasicTimer6Stop(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);       // 清除计数器中断标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE); // 关闭计数器中断
    
    TIM_Cmd(TIM6, DISABLE);                     // 使能
}


/*!
 *  功  能: 基本定时器7 停止计时
 *  param1: 无
 *  retval: 无返回值
 */
void BasicTimer7Stop(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);       // 清除计数器中断标志位
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE); // 关闭计数器中断
    
    TIM_Cmd(TIM7, DISABLE);                     // 使能
}



/*!
 *  功  能: 使能基本定时器6 的中断
 *  param1: 无
 *  retval: 无返回值
 *
 *  注  意: 基本定时器只有 更新中断，没有捕获/比较中断
 */
void BasicTimer6IntEnable(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);               // 清除计数器中断标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);          // 开启计数器中断    
}


/*!
 *  功  能: 使能基本定时器的中断
 *  param1: 无
 *  retval: 无返回值
 *
 *  注  意: 基本定时器只有 更新中断，没有捕获/比较中断
 */
void BasicTimer7IntEnable(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);               // 清除计数器中断标志位
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);          // 开启计数器中断    
}


/*!
 *  功  能: 禁止基本定时器6 的中断
 *  param1: 无
 *  retval: 无返回值
 */
void BasicTimer6IntDisable(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);               // 清除计数器中断标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);         // 关闭计数器中断    
}


/*!
 *  功  能: 禁止基本定时器7 的中断
 *  param1: 无
 *  retval: 无返回值
 */
void BasicTimer7IntDisable(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);               // 清除计数器中断标志位
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);         // 关闭计数器中断    
}


/*!
 *  功  能: 获取基本定时器6 的中断状态
 *  param1: 无
 *  retval: RESET = 0, SET = !RESET
 *
 *  注  意: 基本定时器只有 更新中断，没有捕获/比较中断
 */
ITStatus BasicTimer6GetIntStatus(void)
{
    return TIM_GetITStatus( TIM6, TIM_IT_Update );      // 获取定时器6 中断状态 
}


/*!
 *  功  能: 获取基本定时器7 的中断状态
 *  param1: 无
 *  retval: RESET = 0, SET = !RESET
 *
 *  注  意: 基本定时器只有 更新中断，没有捕获/比较中断
 */
ITStatus BasicTimer7GetIntStatus(void)
{
    return TIM_GetITStatus( TIM7, TIM_IT_Update );      // 获取定时器7 中断状态  
}


/*!
 *  功  能: 清除基本定时器6 的中断标志位
 *  param1: 无
 *  retval: 无返回值
 *
 *  注  意: 基本定时器只有 更新中断，没有捕获/比较中断
 */
void BasicTimer6ClearIntFlag(void)
{
    TIM_ClearITPendingBit( TIM6, TIM_FLAG_Update );     // 清除定时器6 中断标志位
}


/*!
 *  功  能: 清除基本定时器7 的中断标志位
 *  param1: 无
 *  retval: 无返回值
 *
 *  注  意: 基本定时器只有 更新中断，没有捕获/比较中断
 */
void BasicTimer7ClearIntFlag(void)
{
    TIM_ClearITPendingBit( TIM7, TIM_FLAG_Update );     // 清除定时器7 中断标志位
}