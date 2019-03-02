// Adopted from https://github.com/ljos/MFRC522/blob/master/examples/check_firmware/check_firmware.ino

#include <stdbool.h>
#include <stdint.h>
#include "arch/avr/mach.hpp"

#include "cpu/avr/abi.hpp"
#include "cpu/avr/drivers/comm/mfrc522.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "cpu/avr/spi.h"
#include "cpu/avr/spi_polled.h"
#include "cpu/avr/usart0.h"

#include <stdio.h>



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
    MFRC522__SELECT::out,
    MFRC522__RESET::out
> nfc;


void main(void) {
    MFRC522__SELECT::set_mode(pin::mode::OUTPUT);
    MFRC522__RESET::set_mode(pin::mode::OUTPUT);
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
