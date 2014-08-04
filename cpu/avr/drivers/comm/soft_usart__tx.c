// =============================================================================
// Software USART driver, transmitter module.
// =============================================================================

#include "cpu/avr/drivers/comm/soft_usart__tx.h"


#ifdef SOFT_USART__TX__DATA__REG
register uint8_t soft_usart__tx__data asm(QUOTE(SOFT_USART__TX__DATA__REG));
#else
volatile uint8_t soft_usart__tx__data;
#endif


void soft_usart__tx__rate__set(const uint16_t rate) {
}


void soft_usart__tx__start(void) {
}


void soft_usart__tx__stop(void) {
}


void soft_usart__tx__write(const uint8_t data) {
    // no checks performed
    soft_usart__tx__data = data;
}


void soft_usart__tx__run(void) {
}
