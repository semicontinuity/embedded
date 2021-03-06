// =============================================================================
// MODBUS RTU driver test.
// =============================================================================


#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"

#include "drivers/out/rts.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>



int main(void) {
    rts__init();

    display__init();
    display__render_packed(0);

    usart0__init();
    usart0__rx__enabled__set(1);    
    usart0__tx__enabled__set(1);    

    for(;;) {
        uint8_t c = usart0__in__read();
        display__render_packed(c);

        rts__set(1);
        _delay_ms(100);
        usart0__out__write(c);
        _delay_ms(100);
        rts__set(0);
    }

    return 0;
}
