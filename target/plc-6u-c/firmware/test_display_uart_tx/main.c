// =============================================================================
// Simple test for USART and display.
// =============================================================================


#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "drivers/out/rts.h"

#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>


int main(void) {
    rts__init();
    rts__set(1);

    uint8_t counter = 0;
    uint8_t c = 'a';

    // display
    display__init();
    display__render_packed(0);

    USART0_REG_C |= (1<<usart0__stop_bits__BIT);
    usart0__rate__set(USART0__BAUD_RATE);
    usart0__tx__enabled__set(1);    

    for(;;) {
        usart0__out__write(c++);
        loop_until_bit_is_set(usart0__tx__complete__value__HOST, usart0__tx__complete__value__BIT);
        if (c == ('z' + 1)) {
            usart0__out__write(13);
            loop_until_bit_is_set(usart0__tx__complete__value__HOST, usart0__tx__complete__value__BIT);
            usart0__out__write(10);
            loop_until_bit_is_set(usart0__tx__complete__value__HOST, usart0__tx__complete__value__BIT);
 
            c = 'a';
            _delay_ms(1000);
            display__render_packed(++counter);
        }
    }

    return 0;
}
