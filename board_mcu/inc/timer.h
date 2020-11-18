#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include "stm32f10x.h"

void BasicTimerDeInit(void);
        
void BasicTimer6Init(uint8_t preemptionPriority, uint8_t subPriority);

void BasicTimer7Init(uint8_t preemptionPriority, uint8_t subPriority);

void BasicTimer6Start(void);

void BasicTimer7Start(void);

void BasicTimer6Stop(void);

void BasicTimer7Stop(void);

void BasicTimer6IntEnable(void);

void BasicTimer7IntEnable(void);

void BasicTimer6IntDisable(void);

void BasicTimer7IntDisable(void);

ITStatus BasicTimer6GetIntStatus(void);

ITStatus BasicTimer7GetIntStatus(void);

void BasicTimer6ClearIntFlag(void);

void BasicTimer7ClearIntFlag(void);

#endif  /* timer.h */