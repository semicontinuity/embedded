// =============================================================================
// Test for Nokia5110 LCD
// =============================================================================

#include "nokia5110.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    usart0__init();
    usart0__rx__enabled__set(1);

    lcd__init();
    lcd__clear();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        char c = usart0__in__read();
        if (c == 0) {
            lcd__terminal__reset();
        } else if (c == 1) {
            c = usart0__in__read();
            lcd__contrast(c);
        } else {
            lcd__terminal__putch(c);
        }
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
