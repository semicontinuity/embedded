// =============================================================================
// Generic ring buffer for data transmission.
// Data are stored in tx_ring_buffer__data
// from head (read position) up to tail (write position) with possible wrapping.
//
// There are two flags associated with the buffer:
// - tx_ring_buffer__not_empty (indicates that it's possible to read)
// - tx_ring_buffer__not_full (indicates that it's possible to write)
// These flags help to understand the state of the buffer when head==tail.
// They are updated after get and put operations,
// and can thus be used to e.g. to trigger interupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#ifndef TX_RING_BUFFER_H
#define TX_RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include "util/bitops.h"


#if defined(TX_RING_BUFFER__NOT_EMPTY__HOST) && defined(TX_RING_BUFFER__NOT_EMPTY__BIT)
DEFINE_BITVAR(tx_ring_buffer__not_empty, TX_RING_BUFFER__NOT_EMPTY__HOST, TX_RING_BUFFER__NOT_EMPTY__BIT);
#endif

#if defined(TX_RING_BUFFER__NOT_FULL__HOST) && defined(TX_RING_BUFFER__NOT_FULL__BIT)
DEFINE_BITVAR(tx_ring_buffer__not_full, TX_RING_BUFFER__NOT_FULL__HOST, TX_RING_BUFFER__NOT_FULL__BIT);
#endif

inline bool tx_ring_buffer__is_writable(void) { return tx_ring_buffer__not_full__is_set(); }
inline bool tx_ring_buffer__is_readable(void) { return tx_ring_buffer__not_empty__is_set(); }


#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


#ifdef TX_RING_BUFFER__HEAD__REG
register volatile uint8_t* tx_ring_buffer__head asm(QUOTE(TX_RING_BUFFER__HEAD__REG));
#else
extern volatile uint8_t* tx_ring_buffer__head;
#endif


#ifdef TX_RING_BUFFER__TAIL__REG
register volatile uint8_t* tx_ring_buffer__tail asm(QUOTE(TX_RING_BUFFER__TAIL__REG));
#else
extern volatile uint8_t* tx_ring_buffer__tail;
#endif


/**
 * Initializes the buffer.
 */
void tx_ring_buffer__start(void);

/**
 * Tells, whether the head pointer is the same as the tail pointer.
 */
bool tx_ring_buffer__is_at_limit(void);

/**
 * Waits until the head pointer and the tail pointer are different.
 */
void tx_ring_buffer__wait_until_not_at_limit(void);

/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 */
uint8_t tx_ring_buffer__get(void);

/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 */
void tx_ring_buffer__put(const uint8_t value);


#endif