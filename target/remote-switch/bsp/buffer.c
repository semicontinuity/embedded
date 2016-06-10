// =============================================================================
// Non-circular buffer.
// Data are stored in buffer__data up to buffer__limit_ptr.
// Use carefully - no bounds checking.
// =============================================================================

#include "buffer.h"
#if defined(BUFFER__POSITION_PTR__REG) || defined(BUFFER__LIMIT_PTR__REG)
#include "cpu/avr/asm.h"
#endif

uint8_t buffer__data[BUFFER__SIZE];

/**
 * Current read position.
 */
#ifndef BUFFER__POSITION_PTR__REG
volatile uint8_t* buffer__position_ptr;
#endif

/**
 * Points to the end of data in the buffer; the current write position.
 */
#ifndef BUFFER__LIMIT_PTR__REG
volatile uint8_t* buffer__limit_ptr;
#endif



/**
 * Makes the buffer ready for writing.
 * (The limit is set to the beginning of the buffer)
 */
void buffer__clear(void) {
    LOAD_ADDRESS(buffer__limit_ptr, buffer__data);
}

/**
 * Makes the buffer ready for reading.
 * (The position is set to the beginning of the buffer)
 */
void buffer__rewind(void) {
    buffer__position_ptr = buffer__data;
}


/**
 * Makes the buffer ready for writing at the current read position.
 */
void buffer__sync(void) {
    buffer__limit_ptr = buffer__position_ptr;
}


/**
 * Initialize the buffer.
 */ 
void buffer__init(void) {
    // possible to save a bit of memory by initializing only one pointer
    // (depends on application)
    buffer__rewind();
    buffer__sync();
}


/**
 * Gets the buffer's position.
 */
uint16_t buffer__position__get(void) {
    return buffer__position_ptr - buffer__data;
}

/**
 * Sets the buffer's position.
 */
void buffer__position__set(const uint16_t position) {
    buffer__position_ptr = buffer__data + position;
}


/**
 * Gets the buffer's limit.
 */
uint16_t buffer__limit__get(void) {
    return buffer__limit_ptr - buffer__data;
}

/**
 * Sets the buffer's limit.
 */
void buffer__limit__set(const uint16_t limit) {
    buffer__limit_ptr = buffer__data + limit;
}



uint8_t buffer__get_u8(void) {
#if defined(BUFFER__POSITION_PTR__REG) && BUFFER__POSITION_PTR__REG==26
    return LOAD_XPLUS(buffer__position_ptr);
#elif defined(BUFFER__POSITION_PTR__REG) && BUFFER__POSITION_PTR__REG==28
    return LOAD_YPLUS(buffer__position_ptr);
#elif defined(BUFFER__POSITION_PTR__REG) && BUFFER__POSITION_PTR__REG==30
    return LOAD_ZPLUS(buffer__position_ptr);
#elif defined(BUFFER__POSITION_PTR__REG)
    return LOAD_ZPLUS(buffer__position_ptr);
#else
    return *buffer__position_ptr++;
#endif
}

uint16_t buffer__get_u16(void) {
    const uint8_t h = buffer__get_u8();
    const uint8_t l = buffer__get_u8();
    return (h << 8) | l;
}


void buffer__put_u8(const uint8_t value) {
#if defined(BUFFER__LIMIT_PTR__REG) && BUFFER__LIMIT_PTR__REG==26
    STORE_XPLUS(buffer__limit_ptr, value);
#elif defined(BUFFER__LIMIT_PTR__REG) && BUFFER__LIMIT_PTR__REG==28
    STORE_YPLUS(buffer__limit_ptr, value);
#elif defined(BUFFER__LIMIT_PTR__REG) && BUFFER__LIMIT_PTR__REG==30
    STORE_ZPLUS(buffer__limit_ptr, value);
#elif defined(BUFFER__LIMIT_PTR__REG)
    STORE_PLUS_VIA_Z(buffer__limit_ptr, value);
#else
    *buffer__limit_ptr++ = value;
#endif
}


void buffer__put_u16(const uint16_t value) {
    buffer__put_u8((uint8_t)(value >> 8));
    buffer__put_u8((uint8_t)(value & 0xFF));
}


bool buffer__is_full(void) {
    return buffer__limit_ptr >= buffer__data + BUFFER__SIZE;
}

bool buffer__is_empty(void) {
    return buffer__position_ptr >= buffer__limit_ptr;
}

