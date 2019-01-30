// =============================================================================
// Non-circular buffer.
// Data are stored in buffer__data up to buffer__limit.
// Use carefully - no bounds checking.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__MODBUS__BUFFER_H
#define CPU__AVR__DRIVERS__COMM__MODBUS__BUFFER_H

#include <stdint.h>
#include <stdbool.h>


#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


extern uint8_t buffer__data[BUFFER__SIZE];

#ifdef BUFFER__POSITION_PTR__REG
register uint8_t* buffer__position_ptr asm(QUOTE(BUFFER__POSITION_PTR__REG));
#else
extern volatile uint8_t* buffer__position_ptr;
#endif


#ifdef BUFFER__LIMIT_PTR__REG
register uint8_t* buffer__limit_ptr asm(QUOTE(BUFFER__LIMIT_PTR__REG));
#else
extern volatile uint8_t* buffer__limit_ptr;
#endif


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
 * Makes the buffer ready for writing at the current read position.
 */
void buffer__sync(void);


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


void buffer__put_u8(const uint8_t value);

void buffer__put_u16(const uint16_t value);


bool buffer__is_full(void);

bool buffer__is_empty(void);


#endif