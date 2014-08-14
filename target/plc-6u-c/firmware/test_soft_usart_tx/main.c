// =============================================================================
// Simple test for software USART and display.
// =============================================================================


#include "cpu/avr/int0.h"
#include "cpu/avr/drivers/comm/soft_usart__tx.h"
#include "cpu/avr/drivers/comm/soft_usart__timer.h"
#include "cpu/avr/drivers/display/segment/static2.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

register uint8_t counter asm("r15");

void send_char(void) {
    display__render_packed(++counter);
    soft_usart__tx__write('A');
}


int main(void) {
    int0__init();
    soft_usart__timer__init();
    display__init();
    
    int0__start();

    send_char();

    sei();    
    for(;;) {
    }

    return 0;
}
