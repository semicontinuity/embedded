// =============================================================================
// Pin
// =============================================================================
#ifndef __ARCH__AVR__PIN_HPP__
#define __ARCH__AVR__PIN_HPP__

#include <stdint.h>
#include "arch/avr/bit.hpp"
#include "arch/avr/mmio_byte.hpp"

namespace pin {
    enum mode { INPUT = 0, OUTPUT = 1 };
};


template<uint16_t BASE_ADDRESS, uint8_t BIT>
class _pin {
public:
    typedef bit<mmio_byte<BASE_ADDRESS + 0>, BIT> in;
    typedef bit<mmio_byte<BASE_ADDRESS + 1>, BIT> dir;
    typedef bit<mmio_byte<BASE_ADDRESS + 2>, BIT> out;

    static void set_mode(const enum pin::mode mode) {
        dir::set(mode);
    }

    static pin::mode get_mode(void) {
        return dir::get() ? pin::mode::OUTPUT : pin::mode::INPUT;
    }
};


#endif
