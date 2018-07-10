// =============================================================================
// Remote switch - buttons handler.
// =============================================================================

#include "services/buttons_handler.h"

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include <avr/interrupt.h>


uint8_t buttons_handler__state = _BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN);



void buttons_handler__run(void) {
    uint8_t state = buttons_handler__read_state_raw();
    if ((state & buttons_handler__state) < buttons_handler__state) {
        // Some button was pressed
        wdt__reset();
        wdt__enable_interrupt();
    } else {
        // Some button was pressed
        wdt__disable_interrupt();
    }
    buttons_handler__state = state;
}



ISR(WDT_vect) {
    wdt__disable_interrupt();
    uint8_t state = buttons_handler__state;
    if (!(state & _BV(IN__BUTTON1__PIN))) {
        led1__toggle();
    }
    if (!(state & _BV(IN__BUTTON2__PIN))) {
        led2__toggle();
    }
    if (!(state & _BV(IN__BUTTON3__PIN))) {
        led3__toggle();
    }
    if (!(state & _BV(IN__BUTTON4__PIN))) {
        led4__toggle();
    }
}
