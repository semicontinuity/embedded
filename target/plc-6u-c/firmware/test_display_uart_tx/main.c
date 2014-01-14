// =============================================================================
// Simple test for USART and display.
// =============================================================================


#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/usart0__tx_polled.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>


int main(void) {
    uint8_t bytes = 0;
    uint8_t c = 'a';

    // display
    display__init();
    display__render_packed(0);

    usart0__rate__set(USART_BAUD_RATE);
    usart0__tx__enabled__set(1);    

    for(;;) {
        usart0__out__write(c++);
        if (c == 'z') c = 'a';
        display__render_packed(++bytes);
    }

    return 0;
}
