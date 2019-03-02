// =============================================================================
// Test (blinking LEDs)
// =============================================================================

#include "drivers/out/led_green.h"
#include "drivers/out/led_red.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>


int main(void) {
    led_red__init();
    led_green__init();

    for(;;) {
        led_red__set(0);
        led_green__set(1);
        _delay_ms(1000);

        led_red__set(1);
        led_green__set(0);
        _delay_ms(1000);
    }

    return 0;
}
