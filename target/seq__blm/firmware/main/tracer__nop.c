// =============================================================================
// Tracer implementation (NOP)
// =============================================================================

#include "services/tracer.h"
#include "twi_slave__tracer.h"


void tracer__init(void) {
    __asm__ __volatile__("tracer__init:");
}

void tracer__start(void) {
}


void inline __attribute__((always_inline)) tracer__io_matrix__in__value(uint8_t column, uint8_t value) {
}

void inline __attribute__((always_inline)) tracer__keyboard__changes(uint8_t column, uint8_t changes) {
}

void inline __attribute__((always_inline)) tracer__comm_encoder__delta(uint8_t column, uint8_t delta) {
}


void __attribute__((weak)) twi__slave__tracer__status(uint8_t status) {
}


void twi__slave__tracer__on_data_reception_started(uint8_t data) {
}

void twi__slave__tracer__on_data_byte_received(uint8_t data) {
}

void twi__slave__tracer__on_data_reception_finished(uint8_t data) {
}


void __attribute__((weak)) twi__slave__tracer__on_data_byte_requested() {}
void __attribute__((weak)) twi__slave__tracer__on_data_byte_transmitted() {}
