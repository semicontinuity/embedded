// =============================================================================
// Buffer.
// =============================================================================

#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stdbool.h>

extern volatile uint8_t *buffer__position;
extern volatile uint8_t *buffer__limit;


void buffer__init(void);

uint8_t buffer__get(void);

void buffer__put(const uint8_t c);

bool buffer__is_full(void);

bool buffer__is_empty(void);


#endif