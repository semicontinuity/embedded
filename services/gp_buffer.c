// =============================================================================
// General-purpose buffer - a thin wrapper around a byte array.
// The buffer is first populated with calls to gp_buffer__put(),
// and then read with calls to gp_buffer__get().
// After calling gp_buffer__start(), the cycle can be repeated.
// (There is one pointer register, associated with the buffer.
// The reason is that on AVR there is severe lack of pointer registers.)
//
// Data are stored in gp_buffer__data.
// The number of items in the buffer can be obtained by gp_buffer__size__get().
//
// Boundary checks are not performed for performance reasons.
// All methods are non-atomic, no locking is performed.
// =============================================================================

#include "services/gp_buffer.h"
#include <avr/io.h>
#include "cpu/avr/asm.h"


uint8_t gp_buffer__data[GP_BUFFER__SIZE];

/**
 * Points to the the current position.
 */
#ifndef GP_BUFFER__PTR__REG
volatile uint8_t* gp_buffer__ptr;
#endif

#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
/**
 * Number of bytes in the buffer.
 */
#ifndef GP_BUFFER__SIZE__REG
volatile uint8_t gp_buffer__size;
#endif
#endif


/**
 * Starts (or resets) the buffer.
 */
void gp_buffer__start(void) {
    gp_buffer__ptr = gp_buffer__data;
#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
    gp_buffer__size = 0;
#endif
}

/**
 * Adjusts the number of bytes in the buffer.
 */
void gp_buffer__size__set(const uint8_t size) {
    gp_buffer__ptr = gp_buffer__data + size;
#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
    gp_buffer__size = size;
#endif
}


/**
 * Number of bytes in the buffer.
 */
uint8_t gp_buffer__size__get(void) {
#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
    return gp_buffer__size;
#else
    return gp_buffer__ptr - gp_buffer__data;
#endif
}


/**
 * Gets the 8-bit value from the buffer.
 * Non-atomic: get() and put() must be called mutually exclusively.
 * Overflow check is not performed.
 */
uint8_t gp_buffer__get(void) {
#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
    ++gp_buffer__size;
#endif

    uint8_t b;
#if defined(GP_BUFFER__PTR__REG) && GP_BUFFER__PTR__REG == 26
    b = LOAD_XPLUS(gp_buffer__ptr);
#elif defined(GP_BUFFER__PTR__REG) && GP_BUFFER__PTR__REG == 28
    b = LOAD_YPLUS(gp_buffer__ptr);
#elif defined(GP_BUFFER__PTR__REG) && GP_BUFFER__PTR__REG == 30
    b = LOAD_ZPLUS(gp_buffer__ptr);
#else
    b = *gp_buffer__ptr++;
#endif

    return b;
}


/**
 * Puts the 8-bit value into the buffer.
 * Non-atomic: get() or put() must be called mutually exclusively, e.g. both in interrupt handlers.
 * Overflow check is not performed.
 */
void gp_buffer__put(const uint8_t value) {
#if defined(GP_BUFFER__PTR__REG) && GP_BUFFER__PTR__REG == 26
    STORE_XPLUS(gp_buffer__ptr, value);
#elif defined(GP_BUFFER__PTR__REG) && GP_BUFFER__PTR__REG == 28
    STORE_YPLUS(gp_buffer__ptr, value);
#elif defined(GP_BUFFER__PTR__REG) && GP_BUFFER__PTR__REG == 30
    STORE_ZPLUS(gp_buffer__ptr, value);
#else
    *gp_buffer__ptr++ = value;
#endif

#if defined(GP_BUFFER__SIZE__USED) && GP_BUFFER__SIZE__USED > 0
    ++gp_buffer__size;
#endif
}
