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
// and can thus be used to e.g. to trigger interupts directly,
// if mapped to hardware interrupt enable bits.
// =============================================================================

#include "services/rx_ring_buffer.h"
#include "cpu/avr/asm.h"


uint8_t rx_ring_buffer__data[RX_RING_BUFFER__SIZE];

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
    if (rx_ring_buffer__head == rx_ring_buffer__data + RX_RING_BUFFER__SIZE)
        rx_ring_buffer__head = rx_ring_buffer__data;
    if (rx_ring_buffer__tail == rx_ring_buffer__head)
        rx_ring_buffer__not_empty__set(0);
    return b;
}


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
    if (rx_ring_buffer__tail == rx_ring_buffer__data + RX_RING_BUFFER__SIZE)
        rx_ring_buffer__tail = rx_ring_buffer__data;
    if (rx_ring_buffer__tail == rx_ring_buffer__head)
        rx_ring_buffer__not_full__set(0);
}
