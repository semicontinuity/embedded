// =============================================================================
// USART transmitter
// =============================================================================

#include "buffer.h"
#include "delay_timer.h"
#include "usart_tx.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/usart0.h"



void usart_tx__enable(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(1);
}

void usart_tx__disable(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(0);
}


ISR(usart0__tx__data_register_empty__interrupt__VECTOR) {
    if (!buffer__is_empty()) {
        usart0__putc(buffer__get_u8());
    }
    else {
        usart_tx__on_frame_sent();
    }
}


ISR(usart0__tx__complete__interrupt__VECTOR) {
}
