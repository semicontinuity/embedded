// =============================================================================
// System timer
// =============================================================================

#include "system_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define PERIODIC_INTERRUPT_VECT    (TIMER0_OVF_vect)

/**
 * This interrupt is invoked F_CPU/1024/256 times per second.
 * (e.g. 45.5 / sec @ 12 MHz)
 */
ISR(PERIODIC_INTERRUPT_VECT) {       
    system_timer__on_system_tick();
}
