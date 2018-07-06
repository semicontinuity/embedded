#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#include "stm32f1xx_hal.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART1_IRQHandler(void);

#endif /* __STM32F10x_IT_H */
