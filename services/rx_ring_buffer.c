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
// and can thus be used to e.g. to trigger interrupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#include "services/rx_ring_buffer.h"
#include <avr/io.h>
#include "cpu/avr/asm.h"


uint8_t rx_ring_buffer__data[RX_RING_BUFFER__SIZE]
#ifdef RX_RING_BUFFER__ALIGNED
#  if RX_RING_BUFFER__SIZE < 256 && ((RX_RING_BUFFER__SIZE & (RX_RING_BUFFER__SIZE - 1)) == 0)
    __attribute__((aligned(RX_RING_BUFFER__SIZE * 2)))
#  else
#    if RX_RING_BUFFER__SIZE == 256
__attribute__((aligned(256)))
#    else
#      error "If RX_RING_BUFFER__ALIGNED, RX_RING_BUFFER__SIZE must be a power of 2 and less than 256"
#    endif
#  endif
#endif
;

/**
 * Points to the the current read position (tail).
 */
#ifndef RX_RING_BUFFER__TAIL__REG
volatile uint8_t* rx_ring_buffer__tail;
#endif

/**
 * Points to the the current write position (head).
 */
#ifndef RX_RING_BUFFER__HEAD__REG
volatile uint8_t* rx_ring_buffer__head;
#endif


/**
 * Initialize the buffer.
 */
void rx_ring_buffer__start(void) {
    rx_ring_buffer__tail = rx_ring_buffer__data;
    rx_ring_buffer__head = rx_ring_buffer__tail;
    rx_ring_buffer__not_empty__set(0);
    rx_ring_buffer__not_full__set(1);
}


/**
 * Tells, whether the tail pointer is the same as the head pointer.
 * It can happen, if the buffer is either completely empty, or completely full.
 */
bool rx_ring_buffer__is_at_limit(void) {
//#if RX_RING_BUFFER__SIZE < 256 || (RX_RING_BUFFER__SIZE == 256 && RX_RING_BUFFER__ALIGNED)
//    return (uint8_t)(uint16_t)rx_ring_buffer__head == (uint8_t)(uint16_t)rx_ring_buffer__tail;
//#else
    return (uint16_t)rx_ring_buffer__head == (uint16_t)rx_ring_buffer__tail;
//#endif
}


/**
 * Waits until the tail pointer and the head pointer are different.
 */
void rx_ring_buffer__wait_until_not_at_limit(void) {
#if RX_RING_BUFFER__SIZE < 256 || (RX_RING_BUFFER__SIZE == 256 && RX_RING_BUFFER__ALIGNED)
    LOOP_WHILE_LO8_EQUAL(rx_ring_buffer__head, rx_ring_buffer__tail);
#else
    while (rx_ring_buffer__is_at_limit());
#endif
}


/**
 * Gets the 8-bit value from the buffer.
 * Must be called only if the buffer is not empty.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
uint8_t rx_ring_buffer__get(void) {
    uint8_t b;
#if defined(RX_RING_BUFFER__TAIL__REG) && RX_RING_BUFFER__TAIL__REG == 26
    b = LOAD_XPLUS(rx_ring_buffer__tail);
#elif defined(RX_RING_BUFFER__TAIL__REG) && RX_RING_BUFFER__TAIL__REG == 28
    b = LOAD_YPLUS(rx_ring_buffer__tail);
#elif defined(RX_RING_BUFFER__TAIL__REG) && RX_RING_BUFFER__TAIL__REG == 30
    b = LOAD_ZPLUS(rx_ring_buffer__tail);
#else
    b = *rx_ring_buffer__tail++;
#endif

#ifdef RX_RING_BUFFER__ALIGNED
#  if RX_RING_BUFFER__SIZE == 256
    LOAD_ADDRESS_HI8_OF(rx_ring_buffer__tail, rx_ring_buffer__data);
#  else
    AND_CONST_LO8(rx_ring_buffer__tail, (0xFF ^ RX_RING_BUFFER__SIZE));
#  endif
#else
    if (rx_ring_buffer__tail == rx_ring_buffer__data + RX_RING_BUFFER__SIZE)
        rx_ring_buffer__tail = rx_ring_buffer__data;
#endif

    rx_ring_buffer__not_full__set(1);

#if defined(RX_RING_BUFFER__ALIGNED)\
    && defined(RX_RING_BUFFER__NOT_EMPTY__HOST)\
    && defined(RX_RING_BUFFER__NOT_EMPTY__BIT)\
    && defined(RX_RING_BUFFER__NOT_EMPTY__IN_BIT_IO_MEM)
    IF_LO8_EQUAL_CLEAR_IO_BIT(rx_ring_buffer__head, rx_ring_buffer__tail, RX_RING_BUFFER__NOT_EMPTY__HOST, RX_RING_BUFFER__NOT_EMPTY__BIT);
#else
    if (__builtin_expect(rx_ring_buffer__is_at_limit(), true)) {
        rx_ring_buffer__not_empty__set(0);
    }
#endif
    return b;
}


/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
void rx_ring_buffer__put(const uint8_t value) {
#if defined(RX_RING_BUFFER__HEAD__REG) && RX_RING_BUFFER__HEAD__REG == 26
    STORE_XPLUS(rx_ring_buffer__head, value);
#elif defined(RX_RING_BUFFER__HEAD__REG) && RX_RING_BUFFER__HEAD__REG == 28
    STORE_YPLUS(rx_ring_buffer__head, value);
#elif defined(RX_RING_BUFFER__HEAD__REG) && RX_RING_BUFFER__HEAD__REG == 30
    STORE_ZPLUS(rx_ring_buffer__head, value);
#else
    *rx_ring_buffer__head++ = value;
#endif

#ifdef RX_RING_BUFFER__ALIGNED
#  if RX_RING_BUFFER__SIZE == 256
    LOAD_ADDRESS_HI8_OF(rx_ring_buffer__head, rx_ring_buffer__data);
#  else
    AND_CONST_LO8(rx_ring_buffer__head, (0xFF ^ RX_RING_BUFFER__SIZE));
#  endif
#else
    if (rx_ring_buffer__head == rx_ring_buffer__data + RX_RING_BUFFER__SIZE)
        rx_ring_buffer__head = rx_ring_buffer__data;
#endif

    rx_ring_buffer__not_empty__set(1);

#if defined(RX_RING_BUFFER__ALIGNED)\
    && defined(RX_RING_BUFFER__NOT_FULL__HOST)\
    && defined(RX_RING_BUFFER__NOT_FULL__BIT)\
    && defined(RX_RING_BUFFER__NOT_FULL__IN_BIT_IO_MEM)
    IF_LO8_EQUAL_CLEAR_IO_BIT(rx_ring_buffer__head, rx_ring_buffer__tail, RX_RING_BUFFER__NOT_FULL__HOST, RX_RING_BUFFER__NOT_FULL__BIT);
#else
    if (__builtin_expect(rx_ring_buffer__is_at_limit(), false)) {
        rx_ring_buffer__not_full__set(0);
    }
#endif
}
