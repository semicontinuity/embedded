// comm_usart_inbound__thread:
// receives and interprets bytes from USART
// runs in the context of main thread
// -----------------------------------------------------------------------------
#include "comm_usart_inbound__thread.h"
#include <cpu/avr/usart0.h>


void comm_usart_inbound__thread__handle_event(uint8_t event) {
    __asm__ __volatile__("comm_usart_inbound__thread__handle_event:");
}


void comm_usart_inbound__thread__start(void) {
    __asm__ __volatile__("comm_usart_inbound__thread__start:");
    usart0__rx__enabled__set(1);
}

bool comm_usart_inbound__thread__is_runnable(void) {
    return __builtin_expect(usart0__rx__complete__value__get(), false);
}

void comm_usart_inbound__thread__run(void) {
    __asm__ __volatile__("comm_usart_inbound__thread__run:");
    comm_usart_inbound__thread__handle_event(usart0__getc());
}
