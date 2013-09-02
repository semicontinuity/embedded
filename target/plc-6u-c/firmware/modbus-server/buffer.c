// =============================================================================
// Non-circular buffer.
// Data are stored between 'position' and 'limit'.
// =============================================================================

#include "buffer.h"


uint8_t buffer__data[BUFFER__SIZE];
volatile uint8_t *buffer__position;
volatile uint8_t *buffer__limit;


void buffer__init(void) {
    buffer__limit = buffer__data;
}


uint8_t buffer__get(void) {
    return *buffer__position++;
}

void buffer__put(const uint8_t c) {
    *buffer__limit++ = c;
}

bool buffer__is_full(void) {
    return buffer__limit >= buffer__data + BUFFER__SIZE;
}

bool buffer__is_empty(void) {
    return buffer__position >= buffer__limit;
}

