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
// There is also SIZE variable, which is the number of items in the buffer.
// It is equal to the difference between HEAD and TAIL (ignoring wrapping).
//
// To read data, it is necessary to set the buffer to the read mode first.
// The pointer is adjusted from HEAD to TAIL.
//
// To write data, it is necessary to set the buffer to the read mode first.
// The pointer is adjusted from TAIL to HEAD.
//
// All methods are non-atomic, no locking is performed.
// =============================================================================

#include "services/gp_ring_buffer.h"
#include <avr/io.h>
#include "cpu/avr/asm.h"


uint8_t gp_ring_buffer__data[GP_RING_BUFFER__SIZE]
#ifdef GP_RING_BUFFER__ALIGNED
#  if GP_RING_BUFFER__SIZE < 256 && ((GP_RING_BUFFER__SIZE & (GP_RING_BUFFER__SIZE - 1)) == 0)
    __attribute__((aligned(GP_RING_BUFFER__SIZE * 2)))
#  else
#    if GP_RING_BUFFER__SIZE == 256
__attribute__((aligned(256)))
#    else
#      error "If GP_RING_BUFFER__ALIGNED, GP_RING_BUFFER__SIZE must be a power of 2 and less than 256"
#    endif
#  endif
#endif
;

/**
 * Points to the the current position (head or tail).
 */
#ifndef GP_RING_BUFFER__PTR__REG
volatile uint8_t* gp_ring_buffer__ptr;
#endif

/**
 * Number of bytes in the buffer.
 */
#ifndef GP_RING_BUFFER__SIZE__REG
volatile uint8_t gp_ring_buffer__size;
#endif


/**
 * Starts the buffer.
 */
void gp_ring_buffer__start(void) {
    __asm__ __volatile__("gp_ring_buffer__start:");
    gp_ring_buffer__ptr = gp_ring_buffer__data;
    gp_ring_buffer__size = 0;
    gp_ring_buffer__not_empty__set(0);
    gp_ring_buffer__not_full__set(1);
}


void gp_ring_buffer__wrap_at_ptr_overflow(void) {
#ifdef GP_RING_BUFFER__ALIGNED
#  if GP_RING_BUFFER__SIZE == 256
    LOAD_ADDRESS_HI8_OF(gp_ring_buffer__ptr, gp_ring_buffer__data);
#  else
    AND_CONST_LO8(gp_ring_buffer__ptr, (0xFFU ^ GP_RING_BUFFER__SIZE));
#  endif
#else
    if (gp_ring_buffer__ptr >= gp_ring_buffer__data + GP_RING_BUFFER__SIZE)
        gp_ring_buffer__ptr = gp_ring_buffer__data;
#endif
}


void gp_ring_buffer__wrap_at_ptr_underflow(void) {
#ifdef GP_RING_BUFFER__ALIGNED
#  if GP_RING_BUFFER__SIZE == 256
    LOAD_ADDRESS_HI8_OF(gp_ring_buffer__ptr, gp_ring_buffer__data);
#  else
    AND_CONST_LO8(gp_ring_buffer__ptr, (0xFFU ^ GP_RING_BUFFER__SIZE));
#  endif
#else
    if (gp_ring_buffer__ptr < gp_ring_buffer__data)
        gp_ring_buffer__ptr = gp_ring_buffer__data + GP_RING_BUFFER__SIZE;
#endif
}


/**
 * Switches the buffer to write mode.
 * Buffer must be in read mode.
 */
void gp_ring_buffer__to_write_mode(void) {
    gp_ring_buffer__ptr += gp_ring_buffer__size;
    gp_ring_buffer__wrap_at_ptr_overflow();
}


/**
 * Switches the buffer to read mode.
 * Buffer must be in write mode.
 */
void gp_ring_buffer__to_read_mode(void) {
    #ifdef GP_RING_BUFFER__ALIGNED
    SUB_LO8(gp_ring_buffer__ptr, gp_ring_buffer__size); // not optimal: extra register used by GCC
    gp_ring_buffer__wrap_at_ptr_underflow();
    #else
    gp_ring_buffer__ptr -= gp_ring_buffer__size;
    #endif
}


/**
 * Gets the 8-bit value from the buffer.
 * Must be called only if the buffer is not empty.
 * Must be called only if the buffer is in read mode.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
uint8_t gp_ring_buffer__get(void) {
    uint8_t b;
#if defined(GP_RING_BUFFER__PTR__REG) && GP_RING_BUFFER__PTR__REG == 26
    b = LOAD_XPLUS(gp_ring_buffer__ptr);
#elif defined(GP_RING_BUFFER__PTR__REG) && GP_RING_BUFFER__PTR__REG == 28
    b = LOAD_YPLUS(gp_ring_buffer__ptr);
#elif defined(GP_RING_BUFFER__PTR__REG) && GP_RING_BUFFER__PTR__REG == 30
    b = LOAD_ZPLUS(gp_ring_buffer__ptr);
#else
    b = *gp_ring_buffer__ptr++;
#endif

    gp_ring_buffer__wrap_at_ptr_overflow();

    gp_ring_buffer__not_full__set(1);
    if (--gp_ring_buffer__size == 0) {
        gp_ring_buffer__not_empty__set(0);
    }
    return b;
}


/**
 * Puts the 8-bit value into the buffer.
 * Must be called only if the buffer is not full.
 * Must be called only if the buffer is in write mode.
 * get() and put() must be called mutually exclusively, e.g. both in interrupt handlers.
 */
void gp_ring_buffer__put(const uint8_t value) {
#if defined(GP_RING_BUFFER__PTR__REG) && GP_RING_BUFFER__PTR__REG == 26
    STORE_XPLUS(gp_ring_buffer__ptr, value);
#elif defined(GP_RING_BUFFER__PTR__REG) && GP_RING_BUFFER__PTR__REG == 28
    STORE_YPLUS(gp_ring_buffer__ptr, value);
#elif defined(GP_RING_BUFFER__PTR__REG) && GP_RING_BUFFER__PTR__REG == 30
    STORE_ZPLUS(gp_ring_buffer__ptr, value);
#else
    *gp_ring_buffer__ptr++ = value;
#endif

    gp_ring_buffer__wrap_at_ptr_overflow();

    gp_ring_buffer__not_empty__set(1);
    if (++gp_ring_buffer__size == GP_RING_BUFFER__SIZE) {
        gp_ring_buffer__not_full__set(0);
    }
}
