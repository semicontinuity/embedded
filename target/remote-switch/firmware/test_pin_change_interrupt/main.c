// =============================================================================
// Remote switch - test pin change interrupt handler.
// =============================================================================


#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include "cpu/avr/gpio.h"
#include "cpu/avr/pin_change_int2.h"

#include <avr/interrupt.h>


ISR(PCINT2_vect) {
    led1__toggle();
}

// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    led1__init();
    led2__init();
    led3__init();
    led4__init();

    ENABLE_PULLUP(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON4);
    pin_change_int2__mask__set(
        _BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN)
    );
}

static void application__start(void) {
    pin_change_int2__start();

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
