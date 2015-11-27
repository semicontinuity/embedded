// =============================================================================
// Generic ring buffer for data reception.
// Data are stored in rx_ring_buffer__data
// from head (read position) up to tail (write position) with possible wrapping.
//
// There are two flags associated with the buffer:
// - rx_ring_buffer__not_empty (indicates that it's possible to read)
// - rx_ring_buffer__not_full (indicates that it's possible to write)
// These flags help to understand the state of the buffer when head==tail.
// They are updated after get and put operations,
// and can thus be used to e.g. to trigger interrupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#include "services/rx_ring_buffer.h"
#include "cpu/avr/asm.h"


uint8_t rx_ring_buffer__data[RX_RING_BUFFER__SIZE]
#ifdef RX_RING_BUFFER__ALIGNED
#  if RX_RING_BUFFER__SIZE < 256 && ((RX_RING_BUFFER__SIZE & (RX_RING_BUFFER__SIZE - 1)) == 0)
__attribute__((aligned(RX_RING_BUFFER__SIZE * 2)))
#  else
#    if RX_RING_BUFFER__SIZE == 256
__attribute__((aligned(256)))
#    else
#      error "If RX_RING_BUFFER__ALIGNED, RX_RING_BUFFER__SIZE must be power of 2 less than 256"
#    endif
#  endif
#endif
;

/**
 * Points to the the current read position (head).
 */
#ifndef RX_RING_BUFFER__HEAD__REG
volatile uint8_t* rx_ring_buffer__head;
#endif

/**
 * Points to the the current write position (tail).
 */
#ifndef RX_RING_BUFFER__TAIL__REG
volatile uint8_t* rx_ring_buffer__tail;
#endif


/**
 * Initialize the buffer.
 */ 
void rx_ring_buffer__start(void) {
    rx_ring_buffer__head = rx_ring_buffer__data;
    rx_ring_buffer__tail = rx_ring_buffer__head;
    rx_ring_buffer__not_empty__set(0);
    rx_ring_buffer__not_full__set(1);
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
void rx_ring_buffer__wait_until_not_at_limit(void) {
#if RX_RING_BUFFER__SIZE < 256 || (RX_RING_BUFFER__SIZE == 256 && RX_RING_BUFFER__ALIGNED)
    LOOP_WHILE_LO8_EQUAL(rx_ring_buffer__tail, rx_ring_buffer__head);
#else
    while (rx_ring_buffer__is_at_limit());
#endif
}


/**
 * Gets the 8-bit value from the buffer.
 * Must be called only if the buffer is not empty.
 */
uint8_t rx_ring_buffer__get(void) {
    uint8_t b;
#if defined(RX_RING_BUFFER__HEAD__REG) && RX_RING_BUFFER__HEAD__REG==26
    b = LOAD_XPLUS(rx_ring_buffer__head);
#elif defined(RX_RING_BUFFER__HEAD__REG) && RX_RING_BUFFER__HEAD__REG==28
    b = LOAD_YPLUS(rx_ring_buffer__head);
#elif defined(RX_RING_BUFFER__HEAD__REG) && RX_RING_BUFFER__HEAD__REG==30
    b = LOAD_ZPLUS(rx_ring_buffer__head);
#else
    b = *rx_ring_buffer__head++;
#endif

#ifdef RX_RING_BUFFER__ALIGNED
#  if RX_RING_BUFFER__SIZE==256
    LOAD_ADDRESS_HI8_OF(rx_ring_buffer__head, rx_ring_buffer__data);
#  else
    AND_CONST_LO8(rx_ring_buffer__head, (0xFF ^ RX_RING_BUFFER__SIZE));
#  endif    
#else
    if (rx_ring_buffer__head == rx_ring_buffer__data + RX_RING_BUFFER__SIZE)
        rx_ring_buffer__head = rx_ring_buffer__data;
#endif

    rx_ring_buffer__not_full__set(1);

#ifdef RX_RING_BUFFER__ALIGNED
    IF_LO8_EQUAL(rx_ring_buffer__tail, rx_ring_buffer__head, rx_ring_buffer__not_empty__set(0));
#else
    if ((uint8_t)(uint16_t)rx_ring_buffer__tail == (uint8_t)(uint16_t)rx_ring_buffer__head)
        rx_ring_buffer__not_empty__set(0);
#endif
    return b;
}


/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 */
void rx_ring_buffer__put(const uint8_t value) {
#if defined(RX_RING_BUFFER__TAIL__REG) && RX_RING_BUFFER__TAIL__REG==26
    STORE_XPLUS(rx_ring_buffer__tail, value);
#elif defined(RX_RING_BUFFER__TAIL__REG) && RX_RING_BUFFER__TAIL__REG==28
    STORE_YPLUS(rx_ring_buffer__tail, value);
#elif defined(RX_RING_BUFFER__TAIL__REG) && RX_RING_BUFFER__TAIL__REG==30
    STORE_ZPLUS(rx_ring_buffer__tail, value);
#else
    *rx_ring_buffer__tail++ = value;
#endif

#ifdef RX_RING_BUFFER__ALIGNED
#  if RX_RING_BUFFER__SIZE==256
    LOAD_ADDRESS_HI8_OF(rx_ring_buffer__tail, rx_ring_buffer__data);
#  else
    AND_CONST_LO8(rx_ring_buffer__tail, (0xFF ^ RX_RING_BUFFER__SIZE));
#  endif    
#else
    if (rx_ring_buffer__tail == rx_ring_buffer__data + RX_RING_BUFFER__SIZE)
        rx_ring_buffer__tail = rx_ring_buffer__data;
#endif

    rx_ring_buffer__not_empty__set(1);

#ifdef RX_RING_BUFFER__ALIGNED
    IF_LO8_EQUAL(rx_ring_buffer__tail, rx_ring_buffer__head, rx_ring_buffer__not_full__set(0));
#else
    if ((uint8_t)(uint16_t)rx_ring_buffer__tail == (uint8_t)(uint16_t)rx_ring_buffer__head)
        rx_ring_buffer__not_full__set(0);
#endif
}
