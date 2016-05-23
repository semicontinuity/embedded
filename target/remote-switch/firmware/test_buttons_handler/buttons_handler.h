// =============================================================================
// Remote switch - buttons handler.
// =============================================================================

#ifndef __BUTTONS_HANDLER_H
#define __BUTTONS_HANDLER_H


#include "cpu/avr/gpio.h"
#include "cpu/avr/wdt.h"
#include "cpu/avr/pin_change_int2.h"


void buttons_handler__init(void) {
    ENABLE_PULLUP(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON4);
    pin_change_int2__mask__set(
        _BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN)
    );
    wdt__reset();
    wdt__prescaler_set(WDTO_2S);
}


void buttons_handler__start(void) {
    pin_change_int2__start();
}


void buttons_handler__run(void);


#endif
