#ifndef __SERVICES__CONSOLE_OUT_H
#define __SERVICES__CONSOLE_OUT_H

#include "util/formatter.h"

void console__out__init(void);

void console__out__start(void);

void console__print(uint8_t c);


void console__println(void) {
    console__print('\r');
    console__print('\n');
}

inline void console__print_error(void) {
    console__print('E');
    console__print('R');
    console__print('R');
    console__print('O');
    console__print('R');
}

inline void console__print_ok(void) {
    console__print('O');
    console__print('K');
}

inline void console__print_byte_as_hex(const uint8_t value) {
    uint16_t hex = formatter__byte_to_hex_chars(value);
    console__print((uint8_t)(hex >> 8));
    console__print((uint8_t)(hex & 0xFF));
}

inline void console__print_bytes_as_hex(uint8_t *bytes, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        console__print_byte_as_hex(bytes[i]);
    }
}

inline void console__print_bool_as_0_or_1(const uint8_t value) {
    console__print((const uint8_t) (value == 0 ? '0' : '1'));
}


#endif