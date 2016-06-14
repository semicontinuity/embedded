// =============================================================================
// Pool controller extender - grab LCD data on rising edge of E and send them.
// =============================================================================

#include "cpu/avr/asm.h"
#include "cpu/avr/int1.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <avr/interrupt.h>



ISR(INT1_vect, ISR_NAKED) {
    usart0__putc(PORT_VALUE(LCD_TAP)); // don't check business
    reti();
}

void int1__run(void) {
    // dummy
}

// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    usart0__init();   

    // interrupt from INT1 pin, rising edge
    INT1__CONFIG__HOST = (INT1__CONFIG__HOST | (1<<ISC11) | (1<<ISC10));
}

void application__start(void) {
    usart0__tx__enabled__set(1);
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
