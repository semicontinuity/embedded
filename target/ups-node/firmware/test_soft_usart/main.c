// =============================================================================
// Test for soft USART
// =============================================================================

#include "soft_usart__timer.h"
#include "soft_usart__rx.h"
#include "soft_usart__tx.h"
#include "cpu/avr/int0.h"
#include <avr/interrupt.h>


void soft_usart__rx__on_data(void) {
    soft_usart__tx__data = soft_usart__rx__data;
    soft_usart__tx__start();
}

void soft_usart__tx__on_complete(void) {
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    soft_usart__rx__init();
    soft_usart__rx__detector__init();
    soft_usart__tx__init();
    soft_usart__timer__init();
    soft_usart__timer__start();
    soft_usart__rx__detector__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
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
