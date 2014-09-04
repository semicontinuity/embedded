#include <stdbool.h>
#include <stdint.h>
//#include <avr/io.h>
#include "arch/avr/io.h"

#include "cpu/avr/abi.hpp"
#include "cpu/avr/drivers/comm/mfrc522.hpp"


template<uint16_t ADDRESS, uint8_t BIT>
class bit {
public:
//    static bool get(void) { return *BYTE::value() & (1 <<  BIT); }
//    static void set(bool value) { if (value) *BYTE::value() |= (1<<BIT); else *BYTE::value() &= ~(1<<BIT);}

//    static volatile uint8_t *host(void)       { return (volatile uint8_t *)HOST; }
//    static bool get(void)       { return *((volatile uint8_t *)HOST) & (1 <<  BIT); }
    static void set(bool value) { if (value) *((volatile uint8_t *)ADDRESS) |= (1<<BIT); else *((volatile uint8_t *)ADDRESS) &= ~(1<<BIT);}
//    static void set1(bool value) { if (value) (*host()) |= (1<<BIT); else (*host()) &= ~(1<<BIT);}
//    static void set1(bool value) { if (value) (*host()) |= (1<<BIT); else (*host()) &= ~(1<<BIT);}

};


template<uint16_t ADDRESS, uint8_t BIT>
class pin
{
public:
    
//    static bool get(void) { return *PORT::in_reg_ptr() & (1 <<  PIN); }
    static void set(bool value) { if (value) *((volatile uint8_t *)ADDRESS) |= (1<<BIT); else *((volatile uint8_t *)ADDRESS) &= ~(1<<BIT);}
//    static void set(bool value) { if (value) *PORT::out_reg_ptr() |= (1<<PIN); else *PORT::out_reg_ptr() &= ~(1<<PIN);}

    typedef bit<ADDRESS + 0, BIT> in;
    typedef bit<ADDRESS + 1, BIT> dir;
    typedef bit<ADDRESS + 2, BIT> out;
};


class spi {
public:
    static uint8_t transfer(const uint8_t data) { return 0; }
};


typedef mfrc522<
    spi,
    pin<MFRC522__SELECT__PORT, MFRC522__SELECT__PIN>::out,
    pin<MFRC522__RESET__PORT, MFRC522__RESET__PIN>::out
> nfc;


void main(void) {
    nfc::init();
    for (;;);
}
