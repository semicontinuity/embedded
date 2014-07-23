// =============================================================================
// Pool controller extender - system_timer & USART test.
// =============================================================================

#include "services/system_timer.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


void on_system_timer_event(void) {
    usart0__out__write('A');
}

// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();
    system_timer__init();
}

static void application__start(void) {
    usart0__tx__enabled__set(1);
    system_timer__start();
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();
    application__start();

    sei();
    for(;;) {
    }

    return 0;
}
