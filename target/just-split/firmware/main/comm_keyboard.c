#include "comm_keyboard.h"

#include <cpu/avr/asm.h>

#include <cpu/avr/usart0.h>
#include <cpu/avr/usart0__tx_polled.h>
#include "services/tx_ring_buffer.h"


void comm_keyboard__start(void) {
    __asm__ __volatile__("comm_keyboard__start:");
    tx_ring_buffer__start();
}


// comm_keyboard__thread:
// extracts events from the ring buffer and sends them via USART
// runs in the context of main thread
// -----------------------------------------------------------------------------


void comm_keyboard__thread__start(void) {
    __asm__ __volatile__("comm_keyboard__thread__start:");
    usart0__tx__enabled__set(1);
}

bool comm_keyboard__thread__is_runnable(void) {
    return __builtin_expect(tx_ring_buffer__is_readable(), false);
}

void comm_keyboard__thread__run(void) {
    __asm__ __volatile__("comm_keyboard__thread__run:");
    uint8_t event = tx_ring_buffer__get();
    usart0__out__write(event);
}
