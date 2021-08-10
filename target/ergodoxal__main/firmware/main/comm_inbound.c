#include "comm_inbound.h"

#include <cpu/avr/usart0.h>


void comm_inbound__start(void) {
    tx_ring_buffer__start();
}


// comm_inbound__thread:
// receives and interprets bytes from USART
// runs in the context of main thread
// -----------------------------------------------------------------------------


void comm_inbound__thread__start(void) {
    usart0__rx__enabled__set(1);
}

bool comm_inbound__thread__is_runnable(void) {
    return __builtin_expect(usart0__rx__complete__value__get(), false);
}

void comm_inbound__thread__run(void) {
    __asm__ __volatile__("comm_inbound__thread__run:");
    uint8_t event = usart0__getc();
}
