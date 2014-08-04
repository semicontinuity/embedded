// =============================================================================
// Simple test for software USART and display.
// =============================================================================


#include "cpu/avr/drivers/comm/soft_usart__tx.h"
#include "cpu/avr/drivers/display/segment/static2.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>


int main(void) {
    display__init();
    display__render_packed(0);

    soft_usart__tx__rate__set(SOFT_USART__BAUD_RATE);

    sei();
    for(;;) {
    }

    return 0;
}
