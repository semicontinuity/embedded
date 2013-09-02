// =============================================================================
// Buffer.
// =============================================================================

#include <stdint.h>
#include <stdbool.h>

#include "buffer.h"


uint8_t buffer__data[BUFFER__SIZE];
uint8_t *buffer__ptr;
uint8_t buffer__remaining;


void buffer__init(void) {
    buffer__clear();
}


void buffer__clear(void) {
    buffer__ptr = buffer__data;
    buffer__remaining = (uint8_t)BUFFER__SIZE;
}
