#pragma once
#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include "stm32f10x.h"

void NMI_Handler(void);

void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);

void SysTick_Handler(void);
void EXTI0_IRQHandler(void);

#endif // __INTERRUPTS_H__
