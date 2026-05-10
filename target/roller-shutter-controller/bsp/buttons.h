// =============================================================================
// The driver for two buttons BUTTON1 and BUTTON2 (active low).
// The buttons must connected to the same port.
// =============================================================================

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button1__init(void) {
    USE_AS_INPUT(BUTTON1);
    ENABLE_PULLUP(BUTTON1);
}

inline void button2__init(void) {
    USE_AS_INPUT(BUTTON2);
    ENABLE_PULLUP(BUTTON2);
}


/**
 * Initialize the button pins.
 */
inline void buttons__init(void) {
    button1__init();
    button2__init();
}


#endif