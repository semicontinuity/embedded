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

#include "device.h"
#include "platform/plc-3u-a/pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Public variables
// -----------------------------------------------------------------------------
volatile uint8_t colors[6];

// Private variables
// -----------------------------------------------------------------------------

register uint8_t t asm("r5");
register uint8_t mask asm("r6");


/**
 * Timer 0 overflow interrupt handler
 */
ISR(TIMER0_OVF_vect)
{

    // if 256 timer overflows happened, start over.
    if (++t == 0) {
        mask = _BV(PWM_0_PIN)|_BV(PWM_1_PIN)|_BV(PWM_2_PIN)|_BV(PWM_3_PIN)|_BV(PWM_4_PIN)|_BV(PWM_5_PIN);
    }

    uint8_t index = 0;
    // Loop unrolled for performance reason
    if (t == colors[index++]) mask &= ~_BV(PWM_0_PIN);
    if (t == colors[index++]) mask &= ~_BV(PWM_1_PIN);
    if (t == colors[index++]) mask &= ~_BV(PWM_2_PIN);
    if (t == colors[index++]) mask &= ~_BV(PWM_3_PIN);
    if (t == colors[index++]) mask &= ~_BV(PWM_4_PIN);
    if (t == colors[index++]) mask &= ~_BV(PWM_5_PIN);

    PWM_PORT = mask;
}
