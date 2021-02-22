// =============================================================================
// Outputs pattern to I2C pins
// SDA: PC4
// SCL: PC5
// =============================================================================

#include <util/delay.h>


// main
// -----------------------------------------------------------------------------

int main(void) __attribute__ ((naked));
int main(void) {

    DDRC |= _BV(4);
    DDRC |= _BV(5);

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
      PORTC |= _BV(4);
      _delay_ms(16000);
      PORTC &= ~_BV(4);

      PORTC |= _BV(5);
      _delay_ms(16000);
      PORTC &= ~_BV(5);

      _delay_ms(8*16000);
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
