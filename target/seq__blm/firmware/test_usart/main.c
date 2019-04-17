// =============================================================================
// Test USART.
// =============================================================================

#include <util/delay.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "drivers/out/alarm.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
//    DDRD = 2;
    alarm__init();
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
        usart0__out__write('A');
        _delay_ms(1000);
        alarm__toggle();
    }

    return 0;
}
