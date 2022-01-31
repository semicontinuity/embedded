#ifndef __UTIL__BITOPS_H
#define __UTIL__BITOPS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif

typedef union {
    uint8_t bytes[2];
    uint16_t word;
} u16_as_bytes;

#define U16(lo, hi) \
({                        \
    u16_as_bytes val;     \
    val.bytes[0] = lo;    \
    val.bytes[1] = hi;    \
    val.word;             \
}) 


// =============================================================================
// Helper macros for bit variables
// =============================================================================
#define BITVAR_SET(host, bit, value) do { if ((value)) (host) |= (1 << (bit)); else (host) &= ~(1 << (bit));} while(0)
#define BITVAR_GET(host, bit) ((host) & (1 << (bit)))


#define DECLARE_BITVAR(name)                \
    INLINE void name##__set(char v);        \
    INLINE bool name##__is_set(void);       \
    INLINE char name##__get(void);

#define DEFINE_BITVAR(name, host, bit)                                                                      \
    INLINE void name##__set_from_bit_opt(const unsigned char v, const unsigned char v_bit) {                \
        (host) &= ~(1U << (bit));                                                                           \
        if ((v & (1U << v_bit))) (host) |= (1U << (bit));                                                   \
    }                                                                                                       \
    INLINE void name##__set(char v)     { if ((v)) (host) |= (1U << (bit)); else (host) &= ~(1U << (bit));} \
    INLINE bool name##__is_set(void)    { return (host) & (1U << (bit)); }                                  \
    INLINE char name##__get(void)       { return (host) & (1U << (bit)); }

#define DECLARE_FAKE_BITVAR(name) \
    INLINE void name##__set(char v)  {} \
    INLINE bool name##__is_set(void) { return false; }


#define DECLARE_BITVAR_WITH_BINDING(name, host, bit) \
INLINE void name##__on_set_0(void);      \
INLINE void name##__on_set_1(void);      \
static INLINE void name##__set(char v) {        \
    if (v) {                                    \
        (host) |= (1 << (bit));                 \
        name##__on_set_1();                     \
    }                                           \
    else {                                      \
        (host) &= ~(1 << (bit));                \
        name##__on_set_0();                     \
    }                                           \
}                                               \
static INLINE bool name##__is_set(void) {       \
    return (host) & (1 << (bit));               \
}


// =============================================================================
// Helper macros to translate bit number in the 32-bit big endian value
// into offset of a byte and bit number inside that byte
// BigEndian means that
//   0th bit in 32-bit value is bit 7 in byte at offset 0
//  31th bit in 32-bit value is bit 0 in byte at offset 3
// =============================================================================

// offset of byte 32-bit value in memory containing given bit
#define UINT32_BIGENDIAN_BYTE_OFFSET(bit) ((bit)/8)

// offset of bit inside a byte of 32-bit value in memory containing given bit
#define UINT32_BIGENDIAN_BIT_IN_BYTE(bit) (7 - ((bit)%8))


#endif