// =============================================================================
// Zero cross detector driver.
// Attached to INT0 pin, low-to-high transition shortly after zero cross.
// =============================================================================

#ifndef __ZERO_CROSS_DETECTOR_H
#define __ZERO_CROSS_DETECTOR_H

#include <avr/io.h>

inline void zero_cross_detector__init(void) {
    // INT0 is on PD2, configure internal pull-up.
    PORTD |= _BV(2);    
    // interrupt on INT0 pin rising edge
    EICRA = (1<<ISC01) | (1<<ISC00);
}


inline void zero_cross_detector__start(void) {
    // Enable interrupt from INT0
    EIMSK |= (1<<INT0);
}

inline void zero_cross_detector__stop(void) {
    // Disable interrupt from INT0
    EIMSK &= ~(1<<INT0);
}

/**
 * The callback, that is called on every rising zero cross
 */
INLINE void on_zero_cross(void);

#endif