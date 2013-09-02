// =============================================================================
// USART receiver
// =============================================================================

#include "buffer.h"
#include "delay_timer.h"
#include "usart_rx.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/usart0.h"


volatile bool usart_rx__enabled;


void usart_rx__enable(void) {
    usart_rx__enabled = true;
}


void usart_rx__disable(void) {
    usart_rx__enabled = false;
}


ISR(usart0__rx__complete__interrupt__VECTOR) {
    const uint8_t c = usart0__getc(); // read character in any case
    delay_timer__start();
    if (usart_rx__enabled) {
        if (!buffer__is_full()) {
            buffer__put(c);
        }
        else {
            usart_rx__on_buffer_overflow();            
        }
    }
    else {
        usart_rx__on_unexpected_data();
    }
}
