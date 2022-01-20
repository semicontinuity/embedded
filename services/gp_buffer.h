// =============================================================================
// General-purpose buffer - a thin wrapper around a byte array.
// The buffer is first populated with calls to gp_buffer__put(),
// and then read with calls to gp_buffer__get().
// After calling gp_buffer__start(), the cycle can be repeated.
// (There is one pointer register, associated with the buffer.
// The reason is that on AVR there is severe lack of pointer registers.)
//
// Data are stored in gp_buffer__data.
// The number of items in the buffer can be obtained by gp_buffer__size__get().
// Boundary checks are not performed for performance reasons.
// =============================================================================

#ifndef GP_BUFFER_H
#define GP_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "util/bitops.h"


#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


#ifdef GP_BUFFER__PTR__REG
register volatile uint8_t* gp_buffer__ptr asm(QUOTE(GP_BUFFER__PTR__REG));
#else
extern volatile uint8_t* gp_buffer__ptr;
#endif

#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
#ifdef GP_BUFFER__SIZE__REG
register volatile uint8_t gp_buffer__size asm(QUOTE(GP_BUFFER__SIZE__REG));
#else
extern volatile uint8_t gp_buffer__size;
#endif
#endif


/**
 * Starts the buffer.
 */
void gp_buffer__start(void);

/**
 * Number of bytes in the buffer.
 */
uint8_t gp_buffer__size__get(void);

/**
 * Gets the 8-bit value from the buffer.
 * Non-atomic: get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 * Overflow check is not performed.
 */
uint8_t gp_buffer__get(void);

/**
 * Puts the 8-bit value into the buffer.
 * Non-atomic: get() or put() must be called mutually exclusively, e.g. both in interrupt handlers.
 * Overflow check is not performed.
 */
void gp_buffer__put(const uint8_t value);


#endif