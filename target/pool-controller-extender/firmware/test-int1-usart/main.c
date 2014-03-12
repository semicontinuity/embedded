// =============================================================================
// Pool controller extender - test.
// =============================================================================

#include "main.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/int1.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <avr/interrupt.h>



void int1__run(void) {
    usart0__out__write('A');
}


// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    usart0__init();
    int1__init();
}

void application__start(void) {
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
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
//        cli();
//        notifications_emitter__run();
//        sei();
    }

    return 0;
}
