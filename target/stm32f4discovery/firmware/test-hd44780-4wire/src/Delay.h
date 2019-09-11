#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx.h"

//#define delay_const 22            //96 MHz
#define delay_const 36            //168 MHz

void Delay_us (uint32_t time);
void Delay_ms (uint32_t time);

#endif
