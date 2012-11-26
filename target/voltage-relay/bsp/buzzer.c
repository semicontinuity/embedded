// =============================================================================
// Buzzer driver.
// =============================================================================

#include "buzzer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/**
 * Buzzer interrupt handler.
 * Called 1000 times per second.
 * (implemented with Timer 0 Compare A interrupt)
 */
ISR(TIMER0_COMPA_vect)
{
    TOGGLE(BUZZER);
}
