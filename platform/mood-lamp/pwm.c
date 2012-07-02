// Controller for driving RGB LED, attached to the 3 pins of the device port.
//
// User API:
// The desired color values for LEDs are specified in the 'colors' variable.
//
// Implementation:
// The 3-channel PWM is implemented in software, with one 8-bit timer (TIMER0).
//
// Bits in the output port are changing like this:
//     +----------+------+     ...   --+
//     |          |      |             |
// ----+          +------+---- ...   --+-----------

#include "device.h"
#include "gpio.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// Public variables
// -----------------------------------------------------------------------------
volatile uint8_t colors[3];

// Private variables
// -----------------------------------------------------------------------------

register uint8_t t asm("r5");
register uint8_t mask asm("r6");


/**
 * Timer 0 overflow interrupt handler
 */
ISR(TIMER0_COMPA_vect)
{

    // if 256 timer overflows happened, start over.
    if (++t == 0) {
//        mask = _BV(PWM_0_PIN)|_BV(PWM_1_PIN)|_BV(PWM_2_PIN);
        DRIVE_HIGH(LED_R);
        DRIVE_HIGH(LED_G);
        DRIVE_HIGH(LED_B);
    }

    uint8_t index = 0;
    // Loop unrolled for performance reason
//    if (t == colors[index++]) mask &= ~_BV(PWM_0_PIN);
//    if (t == colors[index++]) mask &= ~_BV(PWM_1_PIN);
//    if (t == colors[index++]) mask &= ~_BV(PWM_2_PIN);
    if (t == colors[index++]) DRIVE_LOW(LED_R);
    if (t == colors[index++]) DRIVE_LOW(LED_G);
    if (t == colors[index++]) DRIVE_LOW(LED_B);

//    PWM_PORT = mask;
}
