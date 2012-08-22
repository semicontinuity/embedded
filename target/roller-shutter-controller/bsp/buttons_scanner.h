#ifndef __BUTTONS_SCANNER_H
#define __BUTTONS_SCANNER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

#define BUTTONS_MASK (SIGNAL_MASK(BUTTON1) | SIGNAL_MASK(BUTTON2))

extern uint8_t buttons_scanner__status[2];
#define buttons_scanner__pins_changed   buttons_scanner__status[0]
#define buttons_scanner__pins_state     buttons_scanner__status[1]


/**
 * Called periodically to scan buttons.
 * At every call, it will report the buttons state to the callback buttons_scanner__out__put()
 */
inline void buttons_scanner__run(void) {
    uint8_t current_state = PORT_VALUE(BUTTONS) & BUTTONS_MASK;
    buttons_scanner__pins_changed = buttons_scanner__pins_state ^ current_state;
    buttons_scanner__pins_state   = current_state;
}


#endif