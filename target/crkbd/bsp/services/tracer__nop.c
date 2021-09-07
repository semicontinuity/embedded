// =============================================================================
// No-op Tracer
// =============================================================================

#include "services/tracer.h"
#include <cpu/avr/asm.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


void tracer__init(void) {
}

void tracer__start(void) {
}

void inline __attribute__((always_inline)) tracer__io_matrix__in__value(uint8_t column, uint8_t value) {
}

void inline __attribute__((always_inline)) tracer__keyboard__changes(uint8_t column, uint8_t changes) {
}

void inline __attribute__((always_inline)) tracer__comm_encoder__delta(uint8_t column, uint8_t delta) {
}