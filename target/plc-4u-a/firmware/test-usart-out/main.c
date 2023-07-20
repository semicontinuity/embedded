// =============================================================================
// Remote switch - test USART out.
// =============================================================================

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <util/delay.h>

// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();
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
        usart0__out__write('a');
        _delay_ms(1000);
    }

    return 0;
}
