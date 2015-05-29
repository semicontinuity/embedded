// =============================================================================
// Pool controller extender - test.
// =============================================================================

#include "main.h"
#include "cpu/avr/int1.h"
#include "drivers/out/alarm.h"
#include <avr/interrupt.h>



void int1__run(void) {
    alarm__set(1);
}


// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    alarm__init();
    int1__init();
}

void application__start(void) {
    int1__start();
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
    }

    return 0;
}
