// =============================================================================
// Test USART.
// =============================================================================

#include <util/delay.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();
    _delay_ms(200);
}

static void application__start(void) {
    usart0__tx__enabled__set(1);
}


// =============================================================================
// Entry point.
// =============================================================================

int main(void) {
    application__init();
    application__start();

    for(;;) {
        _delay_ms(500);
        usart0__out__write('A');
    }

    return 0;
}
