// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#include <avr/interrupt.h>
#include "drivers/buttons.h"
#include "drivers/hd44780_watcher.h"
#include "flags/notifications_pending__lcd.h"
#include "services/notifications_emitter.h"
#include "services/tx_ring_buffer.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {    
    buttons__init();
    hd44780_watcher__init();
}

static void application__start(void) {
    tx_ring_buffer__start();
    notifications_pending__lcd__set(0);
    usart_rx__start();
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();
    application__start();

    sei();

    // run background tasks
    for(;;) {
//        cli();
//        notifications_emitter__run();
//        sei();
    }

    return 0;
}
