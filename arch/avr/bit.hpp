// =============================================================================
// Bit
// =============================================================================
#ifndef __ARCH__AVR__BIT_HPP__
#define __ARCH__AVR__BIT_HPP__

#include <stdint.h>


template<typename BYTE, uint8_t BIT>
class bit {
public:
    static void set(bool value) {
        if (value)
            *(BYTE::ptr()) |= (1<<BIT);
        else
            *(BYTE::ptr()) &= ~(1<<BIT);
    }
};


#endif
