// =============================================================================
// Simple test for software USART and display.
// =============================================================================


#include "cpu/avr/drivers/comm/soft_usart.h"
#include "cpu/avr/drivers/comm/soft_usart__rx.h"
#include "cpu/avr/drivers/display/segment/static2.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

register uint8_t counter asm("r15");

/** Invoked when a valid frame has been received */
void soft_usart__rx__on_character_received(uint8_t c) {
    display__render_packed(c);
}

/** Invoked when an invalid frame has been received */
void soft_usart__rx__on_frame_error(void) {
}


int main(void) {
    soft_usart__init();
    display__init();
    
    soft_usart__start();

    sei();    
    for(;;) {
    }

    return 0;
}
