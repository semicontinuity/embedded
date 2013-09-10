// =============================================================================
// Non-circular buffer.
// Data are stored in buffer__data up to buffer__limit.
// Use carefully - no bounds checking.
// =============================================================================

#include "buffer.h"
#include "cpu/avr/asm.h"


uint8_t buffer__data[BUFFER__SIZE];

/**
 * Current read position.
 */
#ifndef BUFFER__POSITION__REG
volatile uint8_t* buffer__position;
#endif

/**
 * Points to the end of data in the buffer; the current write position.
 */
#ifndef BUFFER__LIMIT__REG
volatile uint8_t* buffer__limit;
#endif



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
#if BUFFER__POSITION__REG==26
    return LOAD_XPLUS(buffer__position);
#elif BUFFER__POSITION__REG==28
    return LOAD_YPLUS(buffer__position);
#elif BUFFER__POSITION__REG==30
    return LOAD_ZPLUS(buffer__position);
#else
    return *buffer__position++;
#endif
}

uint16_t buffer__get_u16(void) {
    const uint8_t h = buffer__get_u8();
    const uint8_t l = buffer__get_u8();
    return (h << 8) | l;
}


void buffer__put_u8(const uint8_t value) {
#if BUFFER__LIMIT__REG==26
    STORE_XPLUS(buffer__limit, value);
#elif BUFFER__LIMIT__REG==28
    STORE_YPLUS(buffer__limit, value);
#elif BUFFER__LIMIT__REG==30
    STORE_ZPLUS(buffer__limit, value);
#else
    *buffer__limit++ = value;
#endif
}


void buffer__put_u16(const uint16_t value) {
    buffer__put_u8((uint8_t)(value >> 8));
    buffer__put_u8((uint8_t)(value & 0xFF));
}


bool buffer__is_full(void) {
    return buffer__limit >= buffer__data + BUFFER__SIZE;
}

bool buffer__is_empty(void) {
    return buffer__position >= buffer__limit;
}

