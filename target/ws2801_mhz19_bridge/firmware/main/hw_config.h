/*
 * Based on ST Microelectronics STM32 examples
 */

#pragma once
#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#include "stm32f10x.h"

// RCC
void RCC_Config(void);
// packet size for data to be sent to USB
//#define USART_RX_DATA_SIZE   512

void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);

void Set_USBClock(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);

//void Handle_USBAsynchXfer (void);
//void USB_Send_Data(uint8_t data);
//
//void Ports_Config(void);

#endif // __HW_CONFIG_H__
