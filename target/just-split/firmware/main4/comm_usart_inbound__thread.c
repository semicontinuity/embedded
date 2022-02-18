// comm_usart_inbound__thread:
// receives and interprets bytes from USART
// runs in the context of main thread
// -----------------------------------------------------------------------------
#include "comm_usart_inbound__thread.h"
#include "leds_bar__data.h"
#include <cpu/avr/usart0.h>
#include <cpu/avr/wdt.h>
#include <services/gp_buffer.h>


#if defined(COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__HOST) && defined(COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__BIT)
DEFINE_BITVAR(comm_usart_inbound__thread__header_received, COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__HOST, COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__BIT);
#endif


void comm_usart_inbound__thread__reset() {
    __asm__ __volatile__("comm_usart_inbound__thread__reset:");
    gp_buffer__start();
}

void comm_usart_inbound__thread__handle_event(uint8_t event) {
    __asm__ __volatile__("comm_usart_inbound__thread__handle_event:");
    wdt__reset();

    gp_buffer__put(event);
//    if (gp_buffer__size__get() == 4) {
//        gp_buffer__start();
//    }
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
