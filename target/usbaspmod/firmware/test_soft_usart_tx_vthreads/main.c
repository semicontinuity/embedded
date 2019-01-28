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

    led_red__set(1);
    _delay_ms(10000);
    led_green__set(1);

    soft_usart__tx__thread__init();
    USE_AS_OUTPUT(SOFT_USART__TX);
    OUT_1(SOFT_USART__TX);

    soft_usart__tx__write('a');
    sei();

    led_red__set(0);
    for(;;) {
    }

    return 0;
}
