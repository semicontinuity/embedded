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

#include "services/tx_ring_buffer.h"
#include "cpu/avr/asm.h"


uint8_t tx_ring_buffer__data[TX_RING_BUFFER__SIZE];

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
    if (tx_ring_buffer__head == tx_ring_buffer__data + TX_RING_BUFFER__SIZE)
        tx_ring_buffer__head = tx_ring_buffer__data;
    if (tx_ring_buffer__tail == tx_ring_buffer__head)
        tx_ring_buffer__not_empty__set(0);
    return b;
}


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
    if (tx_ring_buffer__tail == tx_ring_buffer__data + TX_RING_BUFFER__SIZE)
        tx_ring_buffer__tail = tx_ring_buffer__data;
    if (tx_ring_buffer__tail == tx_ring_buffer__head)
        tx_ring_buffer__not_full__set(0);
}
