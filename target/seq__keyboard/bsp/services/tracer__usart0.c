// =============================================================================
// Tracer, implemented with USART0
// =============================================================================

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


void tracer__init(void) {
    __asm__ __volatile__("tracer__init:");
    usart0__init();
}

void tracer__start(void) {
    __asm__ __volatile__("tracer__start:");
    usart0__tx__enabled__set(1);
}

void tracer__run(void) {
    usart0__out__write('A');
}
