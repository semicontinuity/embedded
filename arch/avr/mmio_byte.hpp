// =============================================================================
// Memory-mapped byte
// =============================================================================
#ifndef __ARCH__AVR__MMIO_BYTE_HPP__
#define __ARCH__AVR__MMIO_BYTE_HPP__

#include <stdint.h>


template<uint16_t ADDRESS>
class mmio_byte {
public:
    static volatile uint8_t *ptr(void)   { return (volatile uint8_t *)ADDRESS; }
    static void set(const uint8_t value) { *ptr() = value; }
    static uint8_t get(void)             { return *ptr(); }
};


#endif
