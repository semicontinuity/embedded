// =============================================================================
// Pool controller extender - USART test.
// =============================================================================

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "drivers/out/alarm.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    alarm__init();
    usart0__init();
}

static void application__start(void) {
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();
    application__start();

    char i = 0;
    for(;;) {
        uint8_t c = usart0__in__read();
        c = ~c;
        alarm__set(i);
        usart0__out__write(c);
    }

    return 0;
}
