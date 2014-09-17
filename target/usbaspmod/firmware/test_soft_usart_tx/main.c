// =============================================================================
// Simple test for software USART and display.
// =============================================================================


#include "cpu/avr/drivers/comm/soft_usart.h"
#include "cpu/avr/drivers/comm/soft_usart__tx.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

void send_char(void) {
    _delay_ms(200);
    soft_usart__tx__write('A');
}


void soft_usart__rx__on_character_received(uint8_t c) {}

void soft_usart__rx__on_frame_error(void) {}


int main(void) {
    USE_AS_OUTPUT(SOFT_USART__TX);
    OUT_1(SOFT_USART__TX);

    soft_usart__init();
    //soft_usart__start();

    send_char();

    sei();    
    for(;;) {
    }

    return 0;
}
