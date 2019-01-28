// =============================================================================
// I/O test
// =============================================================================

#include <avr/io.h>
#include <util/delay.h>


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {

    DDRB |= (1<<5);
    
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        _delay_ms(1000);
        PORTB |= (1<<5);
        _delay_ms(1000);
        PORTB &= ~(1<<5);
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
