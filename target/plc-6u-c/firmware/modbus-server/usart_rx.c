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
volatile bool usart_rx__frame_received;


void usart_rx__enable(void) {
    usart_rx__enabled = true;
    usart_rx__frame_received = false;
}


void usart_rx__disable(void) {
    usart_rx__enabled = false;
    buffer__clear();
}


void usart_rx__notify_t15_expired(void) {
    usart_rx__disable();
}


void usart_rx__notify_t35_expired(void) {
    usart_rx__frame_received = true;
    delay_timer__stop();
}


bool usart_rx__is_frame_received(void) {
    return usart_rx__frame_received;
}


ISR(usart0__rx__complete__interrupt__VECTOR) {
    delay_timer__start();
    if (usart_rx__enabled) {
        if (--buffer__remaining == 0) {
            usart_rx__disable();
        }
        else {
            *buffer__ptr++ = usart0__getc();
        }
    }
    else {
        buffer__remaining = 0; // received frame will be dropped
    }
}
