// =============================================================================
// ATMEGA48, ATMEGA88, ATMEGA168, ATMEGA328
// =============================================================================
#ifndef __ARCH__AVR__MACH_MX8_HPP__
#define __ARCH__AVR__MACH_MX8_HPP__

#  include "arch/avr/pin.hpp"

#define REG_PINB        0x23
#define REG_DDRB        0x24
#define REG_PORTB       0x25
#define REG_PINC        0x26
#define REG_DDRC        0x27
#define REG_PORTC       0x28
#define REG_PIND        0x29
#define REG_DDRD        0x2A
#define REG_PORTD       0x2B

namespace pin {
    typedef _pin<REG_PINB, 0> b0;
    typedef _pin<REG_PINB, 1> b1;
    typedef _pin<REG_PINB, 2> b2;
    typedef _pin<REG_PINB, 3> b3;
    typedef _pin<REG_PINB, 4> b4;
    typedef _pin<REG_PINB, 5> b5;
    typedef _pin<REG_PINB, 6> b6;
    typedef _pin<REG_PINB, 7> b7;

    typedef _pin<REG_PINC, 0> c0;
    typedef _pin<REG_PINC, 1> c1;
    typedef _pin<REG_PINC, 2> c2;
    typedef _pin<REG_PINC, 3> c3;
    typedef _pin<REG_PINC, 4> c4;
    typedef _pin<REG_PINC, 5> c5;
    typedef _pin<REG_PINC, 6> c6;

    typedef _pin<REG_PIND, 0> d0;
    typedef _pin<REG_PIND, 1> d1;
    typedef _pin<REG_PIND, 2> d2;
    typedef _pin<REG_PIND, 3> d3;
    typedef _pin<REG_PIND, 4> d4;
    typedef _pin<REG_PIND, 5> d5;
    typedef _pin<REG_PIND, 6> d6;
    typedef _pin<REG_PIND, 7> d7;
};

#endif
