/*!
 *  ��ʱ�����  
 *  STM32F103xx  ��ʱ��2-7  --> APB1������ --> 72MHz
 *               ��ʱ��1��8 --> APB2������ --> 72MHz  
 */

#include <stdio.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include "timer.h"

/*!
 *  ��  ��: �ָ�������ʱ�� 6 �� 7 �ļĴ�����Ĭ��ֵ
 *  param1: ��
 *  retval: ��
 */
void BasicTimerDeInit(void)
{
    TIM_DeInit(TIM6);   // �ָ��Ĵ�����Ĭ��ֵ
    TIM_DeInit(TIM7);   // �ָ��Ĵ�����Ĭ��ֵ
}
        
/*!
 *  ��  ��: ������ʱ��6 �ĳ�ʼ��
 *          ������ʱ��6 ���ڲ��� 200ms ���жϣ���Ϊ���ӹ���״ָ̬ʾ�ƵĶ�ʱ�������ӹ���״ָ̬ʾ��ƽʱ����������������
 *  param1: ��ռ���ȼ�
 *  param2: �����ȼ�
 *  retval: �޷���ֵ 
 * 
 *  ע  ��: ������ʱ������һ��16λ�Զ�װ�ؼ���������ֻ�����ϼ���
 *          16λ�ɱ��(��ʵʱ�޸�)Ԥ��Ƶ�������ڶ������ʱ�Ӱ�ϵ��Ϊ1��65536֮���������ֵ��Ƶ
 *          ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 *          ������ʱ��ֻ�����ڴ������� STM32F101xx �� STM32F103xx ϵ��
 */
void BasicTimer6Init(uint8_t preemptionPriority, uint8_t subPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    // ����Ƕ�������жϿ�����NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; // �ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;	            // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);     // Ƕ�������жϿ�������ʼ��
    
    
    // ������ʱ��������
    TIM_DeInit(TIM6);   // �ָ��Ĵ�����Ĭ��ֵ
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);    // ʹ��ʱ��
    TIM_TimeBaseStructure.TIM_Period = 2000-1;              // �Զ���װ�Ĵ�����ֵ����0��ʼ����
    TIM_TimeBaseStructure.TIM_Prescaler = 7100;             // ��������ʱ��Ƶ��CK_CNT����f CK_PSC /(PSC[15:0]+1)
//    TIM_TimeBaseStructure.TIM_ClockDivision               // ʱ�ӷ�Ƶ���ӣ�������ʱ��û��
//    TIM_TimeBaseStructure.TIM_CounterMode                 // ����������ģʽ��������ʱ��ֻ�����ϼ���
//    TIM_TimeBaseStructure.TIM_RepetitionCounter           // �ظ���������ֵ��������ʱ��û��
    
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);     // ��ʼ�� ������ʱ��6
    
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);               // ����������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);          // �����������ж�
    
    TIM_Cmd(TIM6, ENABLE);      // ʹ��
}    
        

/*!
 *  ��  ��: ������ʱ��7 �ĳ�ʼ����1ms�ж�һ��
 *  param1: ��ռ���ȼ�
 *  param2: �����ȼ�
 *  retval: �޷���ֵ 
 * 
 *  ע  ��: ������ʱ������һ��16λ�Զ�װ�ؼ���������ֻ�����ϼ���
 *          16λ�ɱ��(��ʵʱ�޸�)Ԥ��Ƶ�������ڶ������ʱ�Ӱ�ϵ��Ϊ1��65536֮���������ֵ��Ƶ
 *          ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 *          ������ʱ��ֻ�����ڴ������� STM32F101xx �� STM32F103xx ϵ��
 */
void BasicTimer7Init(uint8_t preemptionPriority, uint8_t subPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    // ����Ƕ�������жϿ�����NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;                             // �ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;  // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;	            // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);                                             // Ƕ�������жϿ�������ʼ��
    
    
    // ������ʱ��7 ������
    TIM_DeInit(TIM7);   // �ָ��Ĵ�����Ĭ��ֵ
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);    // ʹ��ʱ��
    TIM_TimeBaseStructure.TIM_Period = 1000-1;             // �Զ���װ�Ĵ�����ֵ����0��ʼ����
    TIM_TimeBaseStructure.TIM_Prescaler = 71;             // ��������ʱ��Ƶ��CK_CNT����f CK_PSC /(PSC[15:0]+1)
//    TIM_TimeBaseStructure.TIM_ClockDivision               // ʱ�ӷ�Ƶ���ӣ�������ʱ��û��
//    TIM_TimeBaseStructure.TIM_CounterMode                 // ����������ģʽ��������ʱ��ֻ�����ϼ���
//    TIM_TimeBaseStructure.TIM_RepetitionCounter           // �ظ���������ֵ��������ʱ��û��
    
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);     // ��ʼ�� ������ʱ��7
    
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);               // ����������жϱ�־λ
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);          // �����������ж�
    
    TIM_Cmd(TIM7, ENABLE);      // ʹ��
    
    BasicTimer7Stop();          // ��ʼ���رն�ʱ��7
} 


/*!
 *  ��  ��: ������ʱ��6 ��ʼ��ʱ
 *  param1: ��
 *  retval: �޷���ֵ
 */
void BasicTimer6Start(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);       // ����������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);  // �����������ж�
    
    TIM_Cmd(TIM6, ENABLE);                      // ʹ��
}


/*!
 *  ��  ��: ������ʱ��7 ��ʼ��ʱ
 *  param1: ��
 *  retval: �޷���ֵ
 */
void BasicTimer7Start(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);       // ����������жϱ�־λ
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);  // �����������ж�
    
    TIM_Cmd(TIM7, ENABLE);                      // ʹ��
}


/*!
 *  ��  ��: ������ʱ��6 ֹͣ��ʱ
 *  param1: ��
 *  retval: �޷���ֵ
 */
void BasicTimer6Stop(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);       // ����������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE); // �رռ������ж�
    
    TIM_Cmd(TIM6, DISABLE);                     // ʹ��
}


/*!
 *  ��  ��: ������ʱ��7 ֹͣ��ʱ
 *  param1: ��
 *  retval: �޷���ֵ
 */
void BasicTimer7Stop(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);       // ����������жϱ�־λ
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE); // �رռ������ж�
    
    TIM_Cmd(TIM7, DISABLE);                     // ʹ��
}



/*!
 *  ��  ��: ʹ�ܻ�����ʱ��6 ���ж�
 *  param1: ��
 *  retval: �޷���ֵ
 *
 *  ע  ��: ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 */
void BasicTimer6IntEnable(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);               // ����������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);          // �����������ж�    
}


/*!
 *  ��  ��: ʹ�ܻ�����ʱ�����ж�
 *  param1: ��
 *  retval: �޷���ֵ
 *
 *  ע  ��: ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 */
void BasicTimer7IntEnable(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);               // ����������жϱ�־λ
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);          // �����������ж�    
}


/*!
 *  ��  ��: ��ֹ������ʱ��6 ���ж�
 *  param1: ��
 *  retval: �޷���ֵ
 */
void BasicTimer6IntDisable(void)
{
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);               // ����������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);         // �رռ������ж�    
}


/*!
 *  ��  ��: ��ֹ������ʱ��7 ���ж�
 *  param1: ��
 *  retval: �޷���ֵ
 */
void BasicTimer7IntDisable(void)
{
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);               // ����������жϱ�־λ
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);         // �رռ������ж�    
}


/*!
 *  ��  ��: ��ȡ������ʱ��6 ���ж�״̬
 *  param1: ��
 *  retval: RESET = 0, SET = !RESET
 *
 *  ע  ��: ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 */
ITStatus BasicTimer6GetIntStatus(void)
{
    return TIM_GetITStatus( TIM6, TIM_IT_Update );      // ��ȡ��ʱ��6 �ж�״̬ 
}


/*!
 *  ��  ��: ��ȡ������ʱ��7 ���ж�״̬
 *  param1: ��
 *  retval: RESET = 0, SET = !RESET
 *
 *  ע  ��: ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 */
ITStatus BasicTimer7GetIntStatus(void)
{
    return TIM_GetITStatus( TIM7, TIM_IT_Update );      // ��ȡ��ʱ��7 �ж�״̬  
}


/*!
 *  ��  ��: ���������ʱ��6 ���жϱ�־λ
 *  param1: ��
 *  retval: �޷���ֵ
 *
 *  ע  ��: ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 */
void BasicTimer6ClearIntFlag(void)
{
    TIM_ClearITPendingBit( TIM6, TIM_FLAG_Update );     // �����ʱ��6 �жϱ�־λ
}


/*!
 *  ��  ��: ���������ʱ��7 ���жϱ�־λ
 *  param1: ��
 *  retval: �޷���ֵ
 *
 *  ע  ��: ������ʱ��ֻ�� �����жϣ�û�в���/�Ƚ��ж�
 */
void BasicTimer7ClearIntFlag(void)
{
    TIM_ClearITPendingBit( TIM7, TIM_FLAG_Update );     // �����ʱ��7 �жϱ�־λ
}