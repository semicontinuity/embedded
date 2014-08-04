// =============================================================================
// Software USART driver, transmitter module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__SOFT_USART__TX_H
#define CPU__AVR__DRIVERS__COMM__SOFT_USART__TX_H

#include <stdint.h>


void soft_usart__tx__rate__set(const uint16_t rate);

void soft_usart__tx__start(void);

void soft_usart__tx__stop(void);

void soft_usart__tx__write(const uint8_t data);

void soft_usart__tx__run(void);


#endif