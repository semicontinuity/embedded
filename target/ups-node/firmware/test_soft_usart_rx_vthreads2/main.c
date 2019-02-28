// =============================================================================
// Test (Soft USART RX)
// =============================================================================

#include "drivers/out/led_red.h"
#include "drivers/out/led_green.h"
#include "soft_usart__timer.h"

#include "cpu/avr/int0.h"
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>



int main(void) {
    led_red__init();
    led_red__set(1);
    led_green__init();
    led_green__set(1);

    soft_usart__timer__init();
    int0__init();
    
    int0__start();

    sei();
    for(;;) {
    }

    return 0;
}
