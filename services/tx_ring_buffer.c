// =============================================================================
// Generic ring buffer for data transmission.
// Data are stored in tx_ring_buffer__data
// from tail (read position) up to head (write position) with possible wrapping.
//
// There are two flags associated with the buffer:
// - tx_ring_buffer__not_empty (indicates that it's possible to read)
// - tx_ring_buffer__not_full (indicates that it's possible to write)
// These flags help to understand the state of the buffer when tail==head.
// They are updated after get and put operations,
// and can thus be used to e.g. to trigger interrupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#include "services/tx_ring_buffer.h"
#include <avr/io.h>
#include "cpu/avr/asm.h"


uint8_t tx_ring_buffer__data[TX_RING_BUFFER__SIZE]
#ifdef TX_RING_BUFFER__ALIGNED
#  if TX_RING_BUFFER__SIZE < 256 && ((TX_RING_BUFFER__SIZE & (TX_RING_BUFFER__SIZE - 1)) == 0)
__attribute__((aligned(TX_RING_BUFFER__SIZE * 2)))
#  else
#    if TX_RING_BUFFER__SIZE == 256
__attribute__((aligned(256)))
#    else
#      error "If TX_RING_BUFFER__ALIGNED, TX_RING_BUFFER__SIZE must be a power of 2 and less than 256"
#    endif
#  endif
#endif
;

/**
 * Points to the the current read position (tail).
 */
#ifndef TX_RING_BUFFER__TAIL__REG
volatile uint8_t* tx_ring_buffer__tail;
#endif

/**
 * Points to the the current write position (head).
 */
#ifndef TX_RING_BUFFER__HEAD__REG
volatile uint8_t* tx_ring_buffer__head;
#endif


/**
 * Initialize the buffer.
 */ 
void tx_ring_buffer__start(void) {
    __asm__ __volatile__("tx_ring_buffer__start:");
    tx_ring_buffer__tail = tx_ring_buffer__data;
    tx_ring_buffer__head = tx_ring_buffer__tail;
    tx_ring_buffer__not_empty__set(0);
    tx_ring_buffer__not_full__set(1);
}


/**
 * Tells, whether the tail pointer is the same as the head pointer.
 * It can happen, if the buffer is either completely empty, or completely full.
 */
bool tx_ring_buffer__is_at_limit(void) {
//#if TX_RING_BUFFER__SIZE < 256 || (TX_RING_BUFFER__SIZE == 256 && TX_RING_BUFFER__ALIGNED)
//    return (uint8_t)(uint16_t)tx_ring_buffer__head == (uint8_t)(uint16_t)tx_ring_buffer__tail;
//#else
    return (uint16_t)tx_ring_buffer__head == (uint16_t)tx_ring_buffer__tail;
//#endif
}


/**
 * Waits until the tail pointer and the head pointer are different.
 */
void tx_ring_buffer__wait_until_not_at_limit(void) {
#if TX_RING_BUFFER__SIZE < 256 || (TX_RING_BUFFER__SIZE == 256 && TX_RING_BUFFER__ALIGNED)
    LOOP_WHILE_LO8_EQUAL(tx_ring_buffer__head, tx_ring_buffer__tail);
#else
    while (tx_ring_buffer__is_at_limit());
#endif
}


/**
 * Gets the 8-bit value from the buffer.
 * Must be called only if the buffer is not empty.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
uint8_t tx_ring_buffer__get(void) {
    uint8_t b;
#if defined(TX_RING_BUFFER__TAIL__REG) && TX_RING_BUFFER__TAIL__REG == 26
    b = LOAD_XPLUS(tx_ring_buffer__tail);
#elif defined(TX_RING_BUFFER__TAIL__REG) && TX_RING_BUFFER__TAIL__REG == 28
    b = LOAD_YPLUS(tx_ring_buffer__tail);
#elif defined(TX_RING_BUFFER__TAIL__REG) && TX_RING_BUFFER__TAIL__REG == 30
    b = LOAD_ZPLUS(tx_ring_buffer__tail);
#else
    b = *tx_ring_buffer__tail++;
#endif

#ifdef TX_RING_BUFFER__ALIGNED
#  if TX_RING_BUFFER__SIZE == 256
    LOAD_ADDRESS_HI8_OF(tx_ring_buffer__tail, tx_ring_buffer__data);
#  else
    AND_CONST_LO8(tx_ring_buffer__tail, (0xFF ^ TX_RING_BUFFER__SIZE));
#  endif
#else
    if (tx_ring_buffer__tail == tx_ring_buffer__data + TX_RING_BUFFER__SIZE)
        tx_ring_buffer__tail = tx_ring_buffer__data;
#endif

    tx_ring_buffer__not_full__set(1);

#if defined(TX_RING_BUFFER__ALIGNED)\
    && defined(TX_RING_BUFFER__NOT_EMPTY__HOST)\
    && defined(TX_RING_BUFFER__NOT_EMPTY__BIT)\
    && defined(TX_RING_BUFFER__NOT_EMPTY__IN_BIT_IO_MEM)
    IF_LO8_EQUAL_CLEAR_IO_BIT(tx_ring_buffer__head, tx_ring_buffer__tail, TX_RING_BUFFER__NOT_EMPTY__HOST, TX_RING_BUFFER__NOT_EMPTY__BIT);
#else
    if (__builtin_expect(tx_ring_buffer__is_at_limit(), true)) {
        tx_ring_buffer__not_empty__set(0);
    }
#endif
    return b;
}


/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
void tx_ring_buffer__put(const uint8_t value) {
#if defined(TX_RING_BUFFER__HEAD__REG) && TX_RING_BUFFER__HEAD__REG == 26
    STORE_XPLUS(tx_ring_buffer__head, value);
#elif defined(TX_RING_BUFFER__HEAD__REG) && TX_RING_BUFFER__HEAD__REG == 28
    STORE_YPLUS(tx_ring_buffer__head, value);
#elif defined(TX_RING_BUFFER__HEAD__REG) && TX_RING_BUFFER__HEAD__REG == 30
    STORE_ZPLUS(tx_ring_buffer__head, value);
#else
    *tx_ring_buffer__head++ = value;
#endif

#ifdef TX_RING_BUFFER__ALIGNED
#  if TX_RING_BUFFER__SIZE == 256
    LOAD_ADDRESS_HI8_OF(tx_ring_buffer__head, tx_ring_buffer__data);
#  else
    AND_CONST_LO8(tx_ring_buffer__head, (0xFF ^ TX_RING_BUFFER__SIZE));
#  endif
#else
    if (tx_ring_buffer__head == tx_ring_buffer__data + TX_RING_BUFFER__SIZE)
        tx_ring_buffer__head = tx_ring_buffer__data;
#endif

    tx_ring_buffer__not_empty__set(1);

#if defined(TX_RING_BUFFER__ALIGNED)\
    && defined(TX_RING_BUFFER__NOT_FULL__HOST)\
    && defined(TX_RING_BUFFER__NOT_FULL__BIT)\
    && defined(TX_RING_BUFFER__NOT_FULL__IN_BIT_IO_MEM)
    IF_LO8_EQUAL_CLEAR_IO_BIT(tx_ring_buffer__head, tx_ring_buffer__tail, TX_RING_BUFFER__NOT_FULL__HOST, TX_RING_BUFFER__NOT_FULL__BIT);
#else
    if (__builtin_expect(tx_ring_buffer__is_at_limit(), false)) {
        tx_ring_buffer__not_full__set(0);
    }
#endif
}
