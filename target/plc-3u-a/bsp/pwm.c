// Controller for driving two RGB LEDS, attached to the 6 pins of the device port.
//
// User API:
// The desired color values for LEDs are specified in the 'colors' variable.
//
// Implementation:
// The 6-channel PWM is implemented in software, with one 8-bit timer (TIMER0).
//
// Bits in the output port are changing like this:
//     +----------+------+     ...   --+
//     |          |      |             |
// ----+          +------+---- ...   --+-----------

#include "pwm.h"
#include "cpu/avr/gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Public variables
// -----------------------------------------------------------------------------
volatile uint8_t colors[8];

// Private variables
// -----------------------------------------------------------------------------

register uint8_t t asm("r5");
register uint8_t mask asm("r6");


/**
 * Timer 0 overflow interrupt handler
 */
ISR(TIMER0_OVF_vect) {

    // if 256 timer overflows happened, start over.
    if (++t == 0) {
        mask = SIGNAL_MASK(PWM_0)|SIGNAL_MASK(PWM_1)|SIGNAL_MASK(PWM_2)|SIGNAL_MASK(PWM_3)|SIGNAL_MASK(PWM_4)|SIGNAL_MASK(PWM_5);
    }

    uint8_t index = 0;
    // Loop unrolled for performance reason
    if (t == colors[index++]) mask &= ~SIGNAL_MASK(PWM_0);
    if (t == colors[index++]) mask &= ~SIGNAL_MASK(PWM_1);
    if (t == colors[index++]) mask &= ~SIGNAL_MASK(PWM_2);
    if (t == colors[index++]) mask &= ~SIGNAL_MASK(PWM_3);
    if (t == colors[index++]) mask &= ~SIGNAL_MASK(PWM_4);
    if (t == colors[index++]) mask &= ~SIGNAL_MASK(PWM_5);

    OUT(PWM, mask);
}
