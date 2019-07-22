#ifndef TRACER_H
#define TRACER_H

#include <stdint.h>


void __attribute__((weak)) tracer__init(void) {}

void __attribute__((weak)) tracer__start(void) {}

void __attribute__((weak)) tracer__io_matrix__in__value(uint8_t column, uint8_t value) {}

void __attribute__((weak)) tracer__keyboard__changes(uint8_t column, uint8_t changes) {}

void __attribute__((weak)) tracer__comm_encoder__delta(uint8_t column, uint8_t delta) {}

#endif
