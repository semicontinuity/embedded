// =============================================================================
// Soft USART TX driver.
// =============================================================================

#ifndef __SOFT_USART__TX_H
#define __SOFT_USART__TX_H

#include <stdint.h>


#ifdef SOFT_USART__TX__DATA__REG
register uint8_t soft_usart__tx__data asm(QUOTE(SOFT_USART__TX__DATA__REG));
#else
extern volatile uint8_t soft_usart__tx__data;
#endif

void soft_usart__tx__init(void);

void soft_usart__tx__start(void);

void soft_usart__tx__on_complete(void);

#endif