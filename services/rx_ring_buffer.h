// =============================================================================
// Generic ring buffer for data transmission.
// Data are stored in rx_ring_buffer__data
// from tail (read position) up to head (write position) with possible wrapping.
//
// There are two flags associated with the buffer:
// - rx_ring_buffer__not_empty (indicates that it's possible to read)
// - rx_ring_buffer__not_full (indicates that it's possible to write)
// These flags help to understand the state of the buffer when tail==head.
// They are updated after get and put operations,
// and can thus be used to e.g. to trigger interupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#ifndef RX_RING_BUFFER_H
#define RX_RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include "util/bitops.h"


#if defined(RX_RING_BUFFER__NOT_EMPTY__HOST) && defined(RX_RING_BUFFER__NOT_EMPTY__BIT)
DEFINE_BITVAR(rx_ring_buffer__not_empty, RX_RING_BUFFER__NOT_EMPTY__HOST, RX_RING_BUFFER__NOT_EMPTY__BIT);
#endif

#if defined(RX_RING_BUFFER__NOT_FULL__HOST) && defined(RX_RING_BUFFER__NOT_FULL__BIT)
DEFINE_BITVAR(rx_ring_buffer__not_full, RX_RING_BUFFER__NOT_FULL__HOST, RX_RING_BUFFER__NOT_FULL__BIT);
#endif

inline bool rx_ring_buffer__is_writable(void) { return rx_ring_buffer__not_full__is_set(); }
inline bool rx_ring_buffer__is_readable(void) { return rx_ring_buffer__not_empty__is_set(); }


#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


#ifdef RX_RING_BUFFER__TAIL__REG
register volatile uint8_t* rx_ring_buffer__tail asm(QUOTE(RX_RING_BUFFER__TAIL__REG));
#else
extern volatile uint8_t* rx_ring_buffer__tail;
#endif


#ifdef RX_RING_BUFFER__HEAD__REG
register volatile uint8_t* rx_ring_buffer__head asm(QUOTE(RX_RING_BUFFER__HEAD__REG));
#else
extern volatile uint8_t* rx_ring_buffer__head;
#endif


/**
 * Initializes the buffer.
 */
void rx_ring_buffer__start(void);

/**
 * Tells, whether the tail pointer is the same as the head pointer.
 */
bool rx_ring_buffer__is_at_limit(void);

/**
 * Waits until the tail pointer and the head pointer are different.
 */
void rx_ring_buffer__wait_until_not_at_limit(void);

/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
uint8_t rx_ring_buffer__get(void);

/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
void rx_ring_buffer__put(const uint8_t value);


#endif