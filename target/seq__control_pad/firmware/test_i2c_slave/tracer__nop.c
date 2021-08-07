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
