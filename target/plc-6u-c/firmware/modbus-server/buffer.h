// =============================================================================
// Non-circular buffer.
// Data are stored in buffer__data up to buffer__limit.
// Use carefully - no bounds checking.
// =============================================================================

#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stdbool.h>


typedef volatile uint8_t* buffer__limit_t;
typedef volatile uint8_t* buffer__position_t;

extern buffer__position_t buffer__position;
extern buffer__limit_t buffer__limit;


/**
 * Initializes the buffer.
 */
void buffer__init(void);

/**
 * Makes the buffer ready for writing.
 * (The limit is set to the beginning of the buffer)
 */
void buffer__clear(void);

/**
 * Makes the buffer ready for reading.
 * (The position is set to the beginning of the buffer)
 */
void buffer__rewind(void);


/**
 * Gets the buffer's position.
 */
uint16_t buffer__position__get(void);

/**
 * Sets the buffer's position.
 */
void buffer__position__set(const uint16_t position);

/**
 * Gets the buffer's limit.
 */
uint16_t buffer__limit__get(void);

/**
 * Sets the buffer's limit.
 */
void buffer__limit__set(const uint16_t limit);


uint8_t buffer__get_u8(void);

uint16_t buffer__get_u16(void);


buffer__limit_t buffer__put_u8(const uint8_t value);

buffer__limit_t buffer__put_u16(const uint16_t value);


bool buffer__is_full(void);

bool buffer__is_empty(void);


#endif