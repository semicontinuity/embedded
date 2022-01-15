// =============================================================================
// General-purpose ring buffer.
// Data are stored in gp_ring_buffer__data
// from tail (read position) up to head (write position) with possible wrapping.
//
// There are two flags associated with the buffer:
// - gp_ring_buffer__not_empty (indicates, that it's possible to read)
// - gp_ring_buffer__not_full (indicates, that it's possible to write)
// These flags help to understand the state of the buffer when tail==head.
// They are updated after get and put operations,
// and can thus be used to e.g. to trigger interupts directly,
// if mapped to hardware interrupt enable bits.
//
// It is necessary to check the corresponding bit,
// before performing read or write operation.
//
// The buffer can be either in read or write mode, because
// internally, there are no separate HEAD and TAIL pointers,
// but only one pointer, which can be either HEAD or TAIL,
// depending on the mode.
// The reason for this is to have only one pointer register,
// because on AVR there is severe lack of pointer registers.
//
// There is also SIZE variable, which is the number of ptrs in the buffer.
// It is equal to the difference between HEAD and TAIL (ignoring wrapping).
//
// To read data, it is necessary to set the buffer to the read mode first.
// The pointer is adjusted from HEAD to TAIL.
//
// To write data, it is necessary to set the buffer to the read mode first.
// The pointer is adjusted from TAIL to HEAD.
// =============================================================================

#ifndef GP_RING_BUFFER_H
#define GP_RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "util/bitops.h"


#if defined(GP_RING_BUFFER__NOT_EMPTY__HOST) && defined(GP_RING_BUFFER__NOT_EMPTY__BIT)
DEFINE_BITVAR(gp_ring_buffer__not_empty, GP_RING_BUFFER__NOT_EMPTY__HOST, GP_RING_BUFFER__NOT_EMPTY__BIT);
#endif

#if defined(GP_RING_BUFFER__NOT_FULL__HOST) && defined(GP_RING_BUFFER__NOT_FULL__BIT)
DEFINE_BITVAR(gp_ring_buffer__not_full, GP_RING_BUFFER__NOT_FULL__HOST, GP_RING_BUFFER__NOT_FULL__BIT);
#endif

inline bool gp_ring_buffer__is_writable(void) { return gp_ring_buffer__not_full__is_set(); }
inline bool gp_ring_buffer__is_readable(void) { return gp_ring_buffer__not_empty__is_set(); }


#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


#ifdef GP_RING_BUFFER__PTR__REG
register volatile uint8_t* gp_ring_buffer__ptr asm(QUOTE(GP_RING_BUFFER__PTR__REG));
#else
extern volatile uint8_t* gp_ring_buffer__ptr;
#endif


#ifdef GP_RING_BUFFER__SIZE__REG
register volatile uint8_t gp_ring_buffer__size asm(QUOTE(GP_RING_BUFFER__SIZE__REG));
#else
extern volatile uint8_t gp_ring_buffer__size;
#endif


/**
 * Starts the buffer.
 */
void gp_ring_buffer__start(void);

/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
uint8_t gp_ring_buffer__get(void);

/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
void gp_ring_buffer__put(const uint8_t value);


#endif