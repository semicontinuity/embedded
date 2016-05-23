// =============================================================================
// Remote switch - test buttons handler.
// =============================================================================

#include "buttons_handler.h"
#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include <avr/interrupt.h>


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    led1__init();
    led2__init();
    led3__init();
    led4__init();
    buttons_handler__init();
}

static void application__start(void) {
    buttons_handler__start();
    sei();
}


// =============================================================================
// Entry point.
// =============================================================================

int main(void) {
    application__init();
    application__start();

    for(;;) {
    }

    return 0;
}
