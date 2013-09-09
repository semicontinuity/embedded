// =============================================================================
// Non-circular buffer.
// Data are stored in buffer__data up to buffer__limit.
// Use carefully - no bounds checking.
// =============================================================================

#include "buffer.h"


uint8_t buffer__data[BUFFER__SIZE];

/**
 * Current read position.
 */
buffer__position_t buffer__position;

/**
 * Points to the end of data in the buffer; the current write position.
 */
buffer__limit_t buffer__limit;


/**
 * Makes the buffer ready for writing.
 * (The limit is set to the beginning of the buffer)
 */
void buffer__clear(void) {
    buffer__limit = buffer__data;
}

/**
 * Makes the buffer ready for reading.
 * (The position is set to the beginning of the buffer)
 */
void buffer__rewind(void) {
    buffer__position = buffer__data;
}

/**
 * Initialize the buffer.
 */ 
void buffer__init(void) {
    buffer__rewind();
}


/**
 * Gets the buffer's position.
 */
uint16_t buffer__position__get(void) {
    return buffer__position - buffer__data;
}

/**
 * Sets the buffer's position.
 */
void buffer__position__set(const uint16_t position) {
    buffer__position = buffer__data + position;
}


/**
 * Gets the buffer's limit.
 */
uint16_t buffer__limit__get(void) {
    return buffer__limit - buffer__data;
}

/**
 * Sets the buffer's limit.
 */
void buffer__limit__set(const uint16_t limit) {
    buffer__limit = buffer__data + limit;
}



uint8_t buffer__get_u8(void) {
    return *buffer__position++;
}

uint16_t buffer__get_u16(void) {
    const uint8_t h = *buffer__position++;
    const uint8_t l = *buffer__position++;
    return (h << 8) | l;
}


buffer__limit_t buffer__put_u8(const uint8_t value) {
    *buffer__limit++ = value;
    return buffer__limit;
}


buffer__limit_t buffer__put_u16(const uint16_t value) {
    *buffer__limit++ = (uint8_t)(value >> 8);
    *buffer__limit++ = (uint8_t)(value & 0xFF);
    return buffer__limit;
}


bool buffer__is_full(void) {
    return buffer__limit >= buffer__data + BUFFER__SIZE;
}

bool buffer__is_empty(void) {
    return buffer__position >= buffer__limit;
}

