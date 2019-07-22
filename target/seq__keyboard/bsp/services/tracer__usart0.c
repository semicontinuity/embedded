// =============================================================================
// Tracer, implemented with USART0
// =============================================================================

#include "services/tracer.h"
#include <cpu/avr/asm.h>
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

void inline __attribute__((always_inline)) tracer__io_matrix__in__value(uint8_t column, uint8_t value) {
//    if (column == 0) {
//        usart0__putc(value);
//    }
}

void inline __attribute__((always_inline)) tracer__keyboard__changes(uint8_t column, uint8_t changes) {
//    if (column == 0) {
//        usart0__putc(changes);
//    }
}

void inline __attribute__((always_inline)) tracer__comm_encoder__delta(uint8_t column, uint8_t delta) {
    if (column == 0) {
        usart0__putc(delta);
    }
}