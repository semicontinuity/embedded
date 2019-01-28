// =============================================================================
// System timer driver.
// Generates all tick signals required by the system.
//
// Implemented with Timer 2,
// programmed to generate 250 COMPA interrupts (system ticks) per second.
// 
// For the CPU frequency 8 MHz:
// system_tick: 8000000/256/125 = 250Hz
//
// For the CPU frequency 1 MHz:
// system_tick: 1000000/32/125 = 250Hz
//
// Then, the following frequencies are generated in software:
// second_tick:      250/250 = 1Hz
// ten_seconds_tick: 1/10 = 1 per 10 seconds
// phase_off:        at the beginning of every second
// phase_ofn:        in the middle of every second
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
