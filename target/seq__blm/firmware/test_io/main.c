// =============================================================================
// Test I/O.
// =============================================================================

#include <util/delay.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "drivers/keyboard__pins.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    keyboard__pins__init();
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

    uint8_t previous_pins = (1 << 3);
    for(;;) {
        uint8_t pins = PINC;
        uint8_t masked_pins = pins & (1 << 3);
        if (previous_pins == masked_pins) continue;

        previous_pins = masked_pins;

        uint8_t c;
        if (masked_pins & (1 << 3))
            c = 'I';
        else
            c = 'i';
        usart0__out__write(c);
//        _delay_ms(200);
    }

    return 0;
}
