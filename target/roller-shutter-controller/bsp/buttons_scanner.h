// =============================================================================
// The scanner service for 2 buttons at pins BUTTON1 and BUTTON2.
// (The buttons must connected to the same port.)
// Does not support concurrent button presses.
// =============================================================================
#ifndef __BUTTONS_SCANNER_H
#define __BUTTONS_SCANNER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>
#include <stdbool.h>


#define BUTTONS_MASK (SIGNAL_MASK(BUTTON1) | SIGNAL_MASK(BUTTON2))


struct buttons_scanner__status {
    uint8_t pins_changed;
    uint8_t pins_state;
};
extern struct buttons_scanner__status buttons_scanner__status;
#define buttons_scanner__pins_changed   buttons_scanner__status.pins_changed
#define buttons_scanner__pins_state     buttons_scanner__status.pins_state


/**
 * Callback function, called by buttons_scanner__run() when any of the buttons has changed state.
 */
INLINE void buttons_scanner__status__on_change(void);


/**
 * Called periodically to scan buttons.
 * Will invoke the callback buttons_scanner__status__on_change() when any of the buttons has changed state.
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