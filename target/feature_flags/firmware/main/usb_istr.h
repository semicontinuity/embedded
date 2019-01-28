/*
 * Based on ST Microelectronics STM32 examples
 */

#pragma once
#ifndef __USB_ISTR_H__
#define __USB_ISTR_H__

#include "usb_conf.h"

void USB_Istr(void);


void EP1_IN_Callback(void);
void EP2_IN_Callback(void);
void EP3_IN_Callback(void);
void EP4_IN_Callback(void);
void EP5_IN_Callback(void);
void EP6_IN_Callback(void);
void EP7_IN_Callback(void);

void EP1_OUT_Callback(void);
void EP2_OUT_Callback(void);
void EP3_OUT_Callback(void);
void EP4_OUT_Callback(void);
void EP5_OUT_Callback(void);
void EP6_OUT_Callback(void);
void EP7_OUT_Callback(void);

void SOF_Callback(void);
#endif // __USB_ISTR_H__
