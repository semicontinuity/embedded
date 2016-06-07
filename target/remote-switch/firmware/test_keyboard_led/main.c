// =============================================================================
// Remote switch - test keyboard.
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"


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
}

static void application__start(void) {
//    sei();
}


// =============================================================================
// Entry point.
// =============================================================================

int main(void) {
    application__init();
    application__start();

    for(;;) {
        uint8_t state = IN(IN__BUTTONS) & (_BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN));

        led1__set(state & _BV(IN__BUTTON1__PIN));
        led2__set(state & _BV(IN__BUTTON2__PIN));
        led3__set(state & _BV(IN__BUTTON3__PIN));
        led4__set(state & _BV(IN__BUTTON4__PIN));
    }

    return 0;
}
