// comm_usart_outbound__thread:
// extracts events from the ring buffer and sends them via USART.
// Runs in the context of main thread.
// -----------------------------------------------------------------------------
#include "comm_usart_outbound__thread.h"

#include <cpu/avr/asm.h>

#include <cpu/avr/usart0.h>
#include <cpu/avr/usart0__tx_polled.h>
#include "services/tx_ring_buffer.h"


void comm_usart_outbound__thread__start(void) {
    __asm__ __volatile__("comm_usart_outbound__thread__start:");
    usart0__tx__enabled__set(1);
}

bool comm_usart_outbound__thread__is_runnable(void) {
    return __builtin_expect(tx_ring_buffer__is_readable(), false);
}

void comm_usart_outbound__thread__run(void) {
    __asm__ __volatile__("comm_usart_outbound__thread__run:");
    uint8_t event = tx_ring_buffer__get();
    usart0__out__write(event);
}
