// Adopted from https://github.com/ljos/MFRC522/blob/master/examples/check_firmware/check_firmware.ino

#include <stdbool.h>
#include <stdint.h>
//#include <avr/io.h>
#include "arch/avr/io.h"

#include "cpu/avr/abi.hpp"
#include "cpu/avr/drivers/comm/mfrc522.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "cpu/avr/spi.h"
#include "cpu/avr/spi_polled.h"
#include "cpu/avr/usart0.h"

#include <stdio.h>




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
    static uint8_t transfer(const uint8_t data) { return spi__exchange(data); }
};

extern "C"{
    FILE * usart_out;
}



int usart_putchar(char c, FILE *stream) {
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = c;
    return 0;
}


template<uint32_t BAUD_RATE>
class usart0 {
public:
    static void init(void) {
        usart0__rate__set(BAUD_RATE);
        usart0__tx__enabled__set(1);
        usart0__rx__enabled__set(1);

        usart_out = fdevopen(usart_putchar, NULL);
        stdout = stdin = usart_out;
    }
};



typedef usart0<USART0__BAUD_RATE> console;

typedef mfrc522<
    spi,
    pin<MFRC522__SELECT__PORT, MFRC522__SELECT__PIN>::out,
    pin<MFRC522__RESET__PORT, MFRC522__RESET__PIN>::out
> nfc;


void main(void) {
    spi__init(SPI_CLKDIV_16);

    console::init();
    puts_P(PSTR("Looking for MFRC522."));
    nfc::init();
    nfc::start();

    const uint8_t version = nfc::getFirmwareVersion();
    if (!version) {
        puts_P(PSTR("Didn't find MFRC522 board."));
        return;
    }

    puts_P(PSTR("Found chip MFRC522."));
    printf_P(PSTR("Firmware ver. 0x%x."), version);
    if (nfc::digitalSelfTestPass()) {
        puts_P(PSTR("Digital self test by MFRC522 passed."));
    } else {
        puts_P(PSTR("Digital self test by MFRC522 failed."));
    }


    for (;;);
}
