// =============================================================================
// No-op tracer
// =============================================================================

#include "services/tracer.h"


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