// =============================================================================
// Sample MODBUS server.
// =============================================================================


#include "buffer.h"
#include "usart_rx.h"
#include "usart_tx.h"

#include <avr/sleep.h>
#include <stdbool.h>


// Module bindings
// -----------------------------------------------------------------------------

volatile bool frame_received;
volatile bool protocol_error;


void usart_rx__on_buffer_overflow(void) {
    usart_rx__disable();
    buffer__limit = buffer__data;
}

void delay_timer__on_t15_expired(void) {
    usart_rx__disable();
}

void usart_rx__on_unexpected_data(void) {
    // received frame will be dropped (size == 0).
    // transmittion will be aborted, if ongoing.
    buffer__limit = buffer__data;
}


void delay_timer__on_t35_expired(void) {
    delay_timer__stop();
    frame_received = true;
}

void usart_tx__on_frame_sent(void) {
    usart_tx__disable();
    frame_received = false;
    usart_rx__enable();
}


// main
// -----------------------------------------------------------------------------

int main(void) {
    buffer__init();
    delay_timer__init();

    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    usart_rx__enable();
    delay_timer__start();

    for(;;) {
        if (frame_received) {
            // process frame
            // send response
            buffer__position = buffer__data;
            usart_tx__enable();
        }
        else {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}
