// =============================================================================
// System timer
// =============================================================================

#include "system_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/**
 * Current phase (0 or 1).
 * Used to implement blinking text.
 * If phase is 1, the display is off. If phase is 0, the display is on.
 * The on phase lasts 125/250 second, the off phase lasts 125/250 second.
 */
static uint8_t phase;

/**
 * System tick interrupt handler.
 * Called 250 times per second.
 * (implemented with Timer 2 Compare A interrupt)
 */
ISR(TIMER2_COMPA_vect)
{
    // 1. invoke system_tick consumers
    on_system_tick();

    // 2. produce phase_tick and second_tick
    static int8_t t;
    if (--t <= 0) {
        if (phase) {
            phase = 0;
            t = 125;
            on_phase_on();
        }
        else {
            phase = 1;
            t = 125;
            on_phase_off();

            // 2.1. invoke second_tick consumers
            on_second_tick();

            // 2.2 produce ten_seconds_tick
            static int8_t s;
            if (--s <= 0) {
                s = 10;
                on_ten_seconds_tick();
            }
        }
    }
}
