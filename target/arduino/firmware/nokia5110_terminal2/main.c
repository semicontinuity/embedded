// =============================================================================
// Terminal with output to Nokia5110 LCD and LED strip
// =============================================================================

#include "nokia5110.h"

#include <avr/interrupt.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    usart0__init();
    usart0__rx__enabled__set(1);

    USE_AS_OUTPUT(LCD__LED);
    
    lcd__init();
    lcd__clear();
    
    lcd__terminal__reset();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        uint8_t c = usart0__in__read();
        if (c == 0) {
            lcd__terminal__reset();
        } else if (c == 1) {
            c = usart0__in__read();
            lcd__contrast(c);
        } else if (c == 2) {
            OUT_1(LCD__LED);
        } else if (c == 3) {
            OUT_0(LCD__LED);
        } else if (c == 13) {
        } else if (c == 10) {
            lcd__terminal__line_feed();
        } else if (c == 0x1F) {
/*            uint8_t count = usart0__in__read();
            for (;;) {
                c = usart0__in__read();
                soft_spi1__write(c);
                if (!(--count)) break;
            }
*/
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
