// =============================================================================
// Simple test for software USART and display.
// =============================================================================


#include "cpu/avr/timer2.h"
#include "cpu/avr/drivers/comm/soft_usart__tx.h"
#include "cpu/avr/drivers/display/segment/static2.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>


void soft_usart__tx__on_write_complete(void) {
    display__render_packed(1);
}


int main(void) {
    timer2__init();

    display__init();
    display__render_packed(0);

    sei();

    soft_usart__tx__write('A');
    for(;;) {
    }

    return 0;
}
