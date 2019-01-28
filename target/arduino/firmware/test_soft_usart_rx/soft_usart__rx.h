// =============================================================================
// Soft USART RX driver.
// =============================================================================

#ifndef __SOFT_USART__RX_H
#define __SOFT_USART__RX_H

#include <stdint.h>
#include "cpu/avr/asm.h"

#ifdef SOFT_USART__RX__DATA__REG
register uint8_t soft_usart__rx__data asm(QUOTE(SOFT_USART__RX__DATA__REG));
#else
extern volatile uint8_t soft_usart__rx__data;
#endif


void soft_usart__rx__init(void);

void soft_usart__rx__start(void);

void soft_usart__rx__on_data(void);


#endif