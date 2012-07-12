#ifndef __BITOPS_H
#define __BITOPS_H

// =============================================================================
// Helper macros for bit variables
// =============================================================================

#define set(name)	do { name##__HOST |= _BV((name##__BIT)); } while(0)
#define clear(name)	do { name##__HOST &= ~_BV((name##__BIT)); } while(0)
#define is_set(name)    (name##__HOST & _BV((name##__BIT)))

#define DECLARE_BITVAR(name, host, bit) \
	static inline void name##__set(void)	{ (host) |= _BV((bit)); }	\
	static inline void name##__clear(void)	{ (host) &= ~_BV((bit)); }	\
	static inline int name##__is_set(void)	{ return (host) & _BV((bit)); }

// =============================================================================
// Helper macros to translate bit number in the 32-bit big endian value
// into offset of a byte and bit number inside that byte
// BigEndian means that
//   0th bit in 32-bit value is bit 7 in byte at offset 0
//  31th bit in 32-bit value is bit 0 in byte at offset 3
// =============================================================================

// offset of byte 32-bit value in memory containing given bit
#define UINT32_BIGENDIAN_BYTE_OFFSET(bit)	((bit)/8)

// offset of bit inside a byte of 32-bit value in memory containing given bit
#define UINT32_BIGENDIAN_BIT_IN_BYTE(bit)	(7 - ((bit)%8))

#endif // __BITOPS_H