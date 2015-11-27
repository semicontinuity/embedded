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
// and can thus be used to e.g. to trigger interrupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#include "services/tx_ring_buffer.h"
#include "cpu/avr/asm.h"


uint8_t tx_ring_buffer__data[TX_RING_BUFFER__SIZE]
#ifdef TX_RING_BUFFER__ALIGNED
#  if TX_RING_BUFFER__SIZE < 256 && ((TX_RING_BUFFER__SIZE & (TX_RING_BUFFER__SIZE - 1)) == 0)
__attribute__((aligned(TX_RING_BUFFER__SIZE * 2)))
#  else
#    if TX_RING_BUFFER__SIZE == 256
__attribute__((aligned(256)))
#    else
#      error "If TX_RING_BUFFER__ALIGNED, TX_RING_BUFFER__SIZE must be power of 2 less than 256"
#    endif
#  endif
#endif
;

/**
 * Points to the the current read position (head).
 */
#ifndef TX_RING_BUFFER__HEAD__REG
volatile uint8_t* tx_ring_buffer__head;
#endif

/**
 * Points to the the current write position (tail).
 */
#ifndef TX_RING_BUFFER__TAIL__REG
volatile uint8_t* tx_ring_buffer__tail;
#endif


/**
 * Initialize the buffer.
 */ 
void tx_ring_buffer__start(void) {
    tx_ring_buffer__head = tx_ring_buffer__data;
    tx_ring_buffer__tail = tx_ring_buffer__head;
    tx_ring_buffer__not_empty__set(0);
    tx_ring_buffer__not_full__set(1);
}


/**
 * Tells, whether the head pointer is the same as the tail pointer.
 */
bool tx_ring_buffer__is_at_limit(void) {
#if TX_RING_BUFFER__SIZE < 256 || (TX_RING_BUFFER__SIZE == 256 && TX_RING_BUFFER__ALIGNED)
    return (uint8_t)(uint16_t)tx_ring_buffer__tail == (uint8_t)(uint16_t)tx_ring_buffer__head;
#else
    return (uint16_t)tx_ring_buffer__tail == (uint16_t)tx_ring_buffer__head;
#endif
}


/**
 * Waits until the head pointer and the tail pointer are different.
 */
void tx_ring_buffer__wait_until_not_at_limit(void) {
#if TX_RING_BUFFER__SIZE < 256 || (TX_RING_BUFFER__SIZE == 256 && TX_RING_BUFFER__ALIGNED)
    LOOP_WHILE_LO8_EQUAL(tx_ring_buffer__tail, tx_ring_buffer__head);
#else
    while (tx_ring_buffer__is_at_limit());
#endif
}


/**
 * Gets the 8-bit value from the buffer.
 * Must be called only if the buffer is not empty.
 */
uint8_t tx_ring_buffer__get(void) {
    uint8_t b;
#if defined(TX_RING_BUFFER__HEAD__REG) && TX_RING_BUFFER__HEAD__REG==26
    b = LOAD_XPLUS(tx_ring_buffer__head);
#elif defined(TX_RING_BUFFER__HEAD__REG) && TX_RING_BUFFER__HEAD__REG==28
    b = LOAD_YPLUS(tx_ring_buffer__head);
#elif defined(TX_RING_BUFFER__HEAD__REG) && TX_RING_BUFFER__HEAD__REG==30
    b = LOAD_ZPLUS(tx_ring_buffer__head);
#else
    b = *tx_ring_buffer__head++;
#endif

#ifdef TX_RING_BUFFER__ALIGNED
#  if TX_RING_BUFFER__SIZE==256
    LOAD_ADDRESS_HI8_OF(tx_ring_buffer__head, tx_ring_buffer__data);
#  else
    AND_CONST_LO8(tx_ring_buffer__head, (0xFF ^ TX_RING_BUFFER__SIZE));
#  endif    
#else
    if (tx_ring_buffer__head == tx_ring_buffer__data + TX_RING_BUFFER__SIZE)
        tx_ring_buffer__head = tx_ring_buffer__data;
#endif

    tx_ring_buffer__not_full__set(1);

#if defined(TX_RING_BUFFER__ALIGNED)\
    && defined(TX_RING_BUFFER__NOT_EMPTY__HOST)\
    && defined(TX_RING_BUFFER__NOT_EMPTY__BIT)\
    && defined(TX_RING_BUFFER__NOT_EMPTY__IN_BIT_IO_MEM)
    IF_LO8_EQUAL_CLEAR_IO_BIT(tx_ring_buffer__tail, tx_ring_buffer__head, TX_RING_BUFFER__NOT_EMPTY__HOST, TX_RING_BUFFER__NOT_EMPTY__BIT);
#else
    if (tx_ring_buffer__is_at_limit())
        tx_ring_buffer__not_empty__set(0);
#endif
    return b;
}


/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 */
void tx_ring_buffer__put(const uint8_t value) {
#if defined(TX_RING_BUFFER__TAIL__REG) && TX_RING_BUFFER__TAIL__REG==26
    STORE_XPLUS(tx_ring_buffer__tail, value);
#elif defined(TX_RING_BUFFER__TAIL__REG) && TX_RING_BUFFER__TAIL__REG==28
    STORE_YPLUS(tx_ring_buffer__tail, value);
#elif defined(TX_RING_BUFFER__TAIL__REG) && TX_RING_BUFFER__TAIL__REG==30
    STORE_ZPLUS(tx_ring_buffer__tail, value);
#else
    *tx_ring_buffer__tail++ = value;
#endif

#ifdef TX_RING_BUFFER__ALIGNED
#  if TX_RING_BUFFER__SIZE==256
    LOAD_ADDRESS_HI8_OF(tx_ring_buffer__tail, tx_ring_buffer__data);
#  else
    AND_CONST_LO8(tx_ring_buffer__tail, (0xFF ^ TX_RING_BUFFER__SIZE));
#  endif    
#else
    if (tx_ring_buffer__tail == tx_ring_buffer__data + TX_RING_BUFFER__SIZE)
        tx_ring_buffer__tail = tx_ring_buffer__data;
#endif

    tx_ring_buffer__not_empty__set(1);

#if defined(TX_RING_BUFFER__ALIGNED)\
    && defined(TX_RING_BUFFER__NOT_FULL__HOST)\
    && defined(TX_RING_BUFFER__NOT_FULL__BIT)\
    && defined(TX_RING_BUFFER__NOT_FULL__IN_BIT_IO_MEM)
    IF_LO8_EQUAL_CLEAR_IO_BIT(tx_ring_buffer__tail, tx_ring_buffer__head, TX_RING_BUFFER__NOT_FULL__HOST, TX_RING_BUFFER__NOT_FULL__BIT);
#else
    if (tx_ring_buffer__is_at_limit())
        tx_ring_buffer__not_full__set(0);
#endif
}
