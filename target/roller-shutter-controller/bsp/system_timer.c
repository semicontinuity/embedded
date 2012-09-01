// =============================================================================
// System timer
// =============================================================================

#include "system_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/**
 * System tick interrupt handler.
 * Called SYSTEM_TIMER__SECOND_TICK_PERIOD times per second (typically, 250).
 * Implemented with Timer 2 Compare A interrupt.
 */
ISR(TIMER2_COMPA_vect)
{
    // 1. invoke system_tick consumers
    system_timer__on_system_tick();

#ifdef SYSTEM_TIMER__SECOND_TICK
    // 2. second_tick
    static int8_t t;
    if (--t == 0) {
        t = 250;
        system_timer__on_second_tick();
    }
#endif
}
