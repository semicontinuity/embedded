#ifndef TRACER_H
#define TRACER_H

#include <stdint.h>


void tracer__init(void);

void tracer__start(void);


void tracer__io_matrix__in__value(uint8_t column, uint8_t value);

void tracer__keyboard__changes(uint8_t column, uint8_t changes);

void tracer__comm_encoder__delta(uint8_t column, uint8_t delta);


#endif
