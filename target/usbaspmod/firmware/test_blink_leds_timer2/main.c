// =============================================================================
// Test (blinking LEDs)
// =============================================================================

#include "drivers/out/led_green.h"
#include "drivers/out/led_red.h"
#include "system_timer.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>


volatile uint8_t counter;
volatile bool phase;

/**
 * Callback function, called by system_timer__run() on every system tick.
 */
void system_timer__on_system_tick(void) {
    if (--counter == 0) {	// div 256
        if (phase) {
            phase = 0;
            led_red__set(0);
            led_green__set(1);     
        }
        else {
            phase = 1;
            led_red__set(1);
            led_green__set(0);
        }
    }
}

int main(void) {
    led_red__init();
    led_green__init();
    system_timer__init();

    system_timer__start();

    sei();
    for(;;) {
    }

    return 0;
}
