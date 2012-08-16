// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Provides basic operations, such as:
//
// - initialization of the segments port
// - turning the display on and off
// - selecting and deselecting individual digits
// - setting the value of segments to be displayed on selected digits.
//
// NOTE: Perhaps, it is easier to drive anodes by changing port direction only?
// (Then, the display thread must be 'stopped')
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__DYNAMIC3_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__DYNAMIC3_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void display__segments__set(const uint8_t v)	{ OUT(DISPLAY_SEGMENTS, v); }

inline void display__digit_1__enable(void)      { USE_AS_OUTPUT(DISPLAY_ANODE1);        }
inline void display__digit_1__disable(void)     { USE_AS_INPUT(DISPLAY_ANODE1);         }
inline void display__digit_1__select(void)      { OUT_1(DISPLAY_ANODE1);                }
inline void display__digit_1__deselect(void)    { OUT_0(DISPLAY_ANODE1);                }

inline void display__digit_2__enable(void)      { USE_AS_OUTPUT(DISPLAY_ANODE2);        }
inline void display__digit_2__disable(void)     { USE_AS_INPUT(DISPLAY_ANODE2);         }
inline void display__digit_2__select(void)      { OUT_1(DISPLAY_ANODE2);                }
inline void display__digit_2__deselect(void)    { OUT_0(DISPLAY_ANODE2);                }

inline void display__digit_3__enable(void)      { USE_AS_OUTPUT(DISPLAY_ANODE3);        }
inline void display__digit_3__disable(void)     { USE_AS_INPUT(DISPLAY_ANODE3);         }
inline void display__digit_3__select(void)      { OUT_1(DISPLAY_ANODE3);                }
inline void display__digit_3__deselect(void)    { OUT_0(DISPLAY_ANODE3);                }


inline void display__init(void) {
    USE_PORT_AS_OUTPUT(DISPLAY_SEGMENTS);
}

inline void display__on(void) {
    display__digit_1__enable();
    display__digit_2__enable();
    display__digit_3__enable();
}


inline void display__off(void) {
    display__digit_1__disable();
    display__digit_2__disable();
    display__digit_3__disable();
}

#endif