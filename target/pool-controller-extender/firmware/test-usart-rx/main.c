// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#include "main.h"
#include "protocol_handler.h"
#include "drivers/out/alarm.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__rx.h"
#include <avr/interrupt.h>


// =============================================================================
// Handlers
// =============================================================================

void comm__rx__on_data(const uint8_t value) {
    protocol_handler__accept(value);
}


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();

    alarm__init();
}

static void application__start(void) {
    usart0__rx__start();
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();
    application__start();

    alarm__set(1);
    sei();

    // run background tasks
    for(;;) {
    }

    return 0;
}
