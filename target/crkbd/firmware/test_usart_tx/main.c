// =============================================================================
// Test firmware for Ergodoxial keyboard
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/asm.h>

#include <cpu/avr/usart0__tx_polled.h>
#include "cpu/avr/usart0.h"



// application
// -----------------------------------------------------------------------------

void application__init(void) {
    usart0__init();
}

void application__start(void) {
    usart0__tx__enabled__set(1);
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

//    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    __asm__ __volatile__("main__loop:");
    for(;;) {
        _delay_ms(1000);
        usart0__out__write('a');
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
