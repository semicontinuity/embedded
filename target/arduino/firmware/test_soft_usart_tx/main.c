// =============================================================================
// Test for soft USART TX
// =============================================================================

#include "soft_usart__timer.h"
#include "soft_usart__tx.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void soft_usart__tx__on_complete(void) {
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    soft_usart__tx__init();
    soft_usart__timer__init();
    soft_usart__timer__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        soft_usart__tx__data = 'x';
        soft_usart__tx__start();
        _delay_ms(100);
    }
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}
