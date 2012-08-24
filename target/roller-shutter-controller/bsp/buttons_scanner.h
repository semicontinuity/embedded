#ifndef __BUTTONS_SCANNER_H
#define __BUTTONS_SCANNER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>
#include <stdbool.h>


#define BUTTONS_MASK (SIGNAL_MASK(BUTTON1) | SIGNAL_MASK(BUTTON2))

extern uint8_t buttons_scanner__status[2];
#define buttons_scanner__pins_changed   buttons_scanner__status[0]
#define buttons_scanner__pins_state     buttons_scanner__status[1]


/**
 * Callback function, called by buttons_scanner__run() when any of the buttons has changed its state.
 */
INLINE void buttons_scanner__status__on_change(void);


/**
 * Called periodically to scan buttons.
 * At every call, it will report the buttons state to the callback buttons_scanner__out__put()
 */
inline static void buttons_scanner__run(void) {
    uint8_t current_state = PORT_VALUE(BUTTONS) & BUTTONS_MASK;
    buttons_scanner__pins_changed = buttons_scanner__pins_state ^ current_state;
    buttons_scanner__pins_state   = current_state;
    if (buttons_scanner__pins_changed != 0) buttons_scanner__status__on_change();
}


inline static bool buttons_scanner__button1__is_changed(void) {
    return buttons_scanner__pins_changed & SIGNAL_MASK(BUTTON1);
}

inline static bool buttons_scanner__button1__is_released(void) {
    return buttons_scanner__pins_state & SIGNAL_MASK(BUTTON1);
}


inline static bool buttons_scanner__button2__is_changed(void) {
    return buttons_scanner__pins_changed & SIGNAL_MASK(BUTTON2);
}

inline static bool buttons_scanner__button2__is_released(void) {
    return buttons_scanner__pins_state & SIGNAL_MASK(BUTTON2);
}


#endif