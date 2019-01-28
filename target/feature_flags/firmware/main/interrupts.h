/*
 * Based on ST Microelectronics STM32 examples
 */

#pragma once
#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include "stm32f10x.h"

// SysTick equal to Clock / 1000 / SYSTICK_PRESCALE
// 1ms == SYSTICK_PRESCALE  clock ticks
#define SYSTICK_PRESCALE	100

extern uint8_t USB_Rx_Buffer[];

void NMI_Handler(void);

void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);

void SysTick_Handler(void);

void USB_LP_CAN1_RX0_IRQHandler(void);
void EXTI0_IRQHandler(void);

void EP1_IN_Callback(void);
void EP3_OUT_Callback(void);
void SOF_Callback(void);

#endif // __INTERRUPTS_H__
