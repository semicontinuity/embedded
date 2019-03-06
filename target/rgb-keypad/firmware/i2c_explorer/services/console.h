#ifndef __SERVICES__CONSOLE_H
#define __SERVICES__CONSOLE_H

#include "util/formatter.h"


#define CONSOLE__BUFFER_LENGTH 128

extern uint8_t console__input_buffer[CONSOLE__BUFFER_LENGTH];
extern uint16_t console__input_length;


void console__init(void);

void console__start(void);

void console__print(uint8_t c);

void console__read_line(void);


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

inline void console__print_bool_as_0_or_1(const uint8_t value) {
    console__print((const uint8_t) (value == 0 ? '0' : '1'));
}


#endif