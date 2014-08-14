// =============================================================================
// MODBUS RTU driver test.
// =============================================================================


#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdint.h>


uint8_t bytes_received;



int main(void) {
    // display
    display__init();
    display__render_packed(0);

    usart0__rate__set(USART_BAUD_RATE);
    usart0__rx__enabled__set(1);    
    usart0__tx__enabled__set(1);    

    for(;;) {
        uint8_t c = usart0__in__read();
        display__render_packed(++bytes_received);
        usart0__out__write(c);
    }

    return 0;
}
