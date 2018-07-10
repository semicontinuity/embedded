// =============================================================================
// Remote switch - buttons handler.
// Buttons must be attached to adjacent pins in the same port.
// =============================================================================

#ifndef __SERVICES__BUTTONS_HANDLER_H
#define __SERVICES__BUTTONS_HANDLER_H


#include "cpu/avr/gpio.h"
#include "cpu/avr/wdt.h"
#include "cpu/avr/pin_change_int2.h"

#define BUTTONS_HANDLER__STATE(b1, b2, b3, b4) (\
    BUTTONS_HANDLER__STATE__FROM_RAW(\
        ((b1) ? _BV(IN__BUTTON1__PIN) : 0) |\
        ((b2) ? _BV(IN__BUTTON2__PIN) : 0) |\
        ((b3) ? _BV(IN__BUTTON3__PIN) : 0) |\
        ((b4) ? _BV(IN__BUTTON4__PIN) : 0)\
    )\
)
#define BUTTONS_HANDLER__STATE__FROM_RAW(raw) ((raw) >> (IN__BUTTON1__PIN < IN__BUTTON4__PIN ? IN__BUTTON1__PIN : IN__BUTTON4__PIN))

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

inline uint8_t buttons_handler__read_state_raw(void) {
    return (uint8_t) (IN(IN__BUTTONS) & (_BV(IN__BUTTON1__PIN) | _BV(IN__BUTTON2__PIN) | _BV(IN__BUTTON3__PIN) | _BV(IN__BUTTON4__PIN)));
}

inline uint8_t buttons_handler__to_state(const uint8_t raw_state) {
    return BUTTONS_HANDLER__STATE__FROM_RAW(raw_state);
}


void buttons_handler__start(void) {
    pin_change_int2__start();
}


void buttons_handler__run(void);


#endif
