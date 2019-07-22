#include "services/console.h"
#include "util/parser.h"
#include "util/formatter.h"

#include <stdint.h>
#include <avr/io.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/usart0__tx_polled.h"

#define PINA    _SFR_IO8 (0x00)
#define DDRA    _SFR_IO8 (0x01)
#define PORTA   _SFR_IO8 (0x02)

uint8_t console__input_buffer[16];
uint16_t console__input_length;


inline void console__read_line(void) {
    console__input_length = 0;
    while (1) {
        uint8_t c = usart0__in__read();

        if (c==13 || c==10) break;
        if (console__input_length < 16) console__input_buffer[console__input_length++] = c;
    }
}

inline void console__println(void) {
    usart0__out__write(10);
}

inline void console__print_error(void) {
    usart0__out__write('E');
    usart0__out__write('R');
    usart0__out__write('R');
    usart0__out__write('O');
    usart0__out__write('R');
}

inline void console__print_ok(void) {
    usart0__out__write('O');
    usart0__out__write('K');
}

inline void console__print_byte_as_hex(const uint8_t value) {
    uint16_t hex = formatter__byte_to_hex_chars(value);
    usart0__out__write((uint8_t)(hex >> 8));
    usart0__out__write((uint8_t)(hex & 0xFF));
}

inline void console__print_bool_as_0_or_1(const uint8_t value) {
    usart0__out__write(value == 0 ? '0' : '1');
}


/**
 * Supported commands:
 * [A-D]:            read PINA..PIND
 * [A-D]R:           configure port A..D for reading
 * [A-D]W:           configure port A..D for writing
 * [A-D][0-7]:       read bit 0-7 of port A..D
 * [A-D][0-7]R:      configure bit 0-7 of port A..D for reading
 * [A-D][0-7]W:      configure bit 0-7 of port A..D for writing
 * [A-D][0-7]=[0-1]: write [0-1] to bit [0-7] of port [A-D]
 * [A-D]=XX:         write hex value XX to port [A-D]
 * AA=XX:            write hex value to memory address AA
 */
void console__run(void) {
    while(1) {
        console__read_line();
        if (console__input_length == 0) continue;

        volatile uint8_t * r;
        switch (console__input_buffer[0]) {
#ifdef PINA
        case 'A': r = &PINA; break;
#endif
        case 'B': r = &PINB; break;
        case 'C': r = &PINC; break;
        case 'D': r = &PIND; break;
        default:
            //console__print_error();
            //console__println();
            //continue;
            r = 0;
        }


        if (console__input_length == 1) {
            // READ BYTE: 'A', 'B', 'C', 'D'
            console__print_byte_as_hex(*r);
            console__println();
        }
        else if (console__input_length == 2) {
            uint8_t c2 = console__input_buffer[1];
            if (c2 == 'R') {
                // CONFIGURE PORT FOR READING: 'AR', 'BR', 'CR', 'DR'
                *(r + 1) = 0x00;
                console__print_ok();
                console__println();
            }
            else if (c2 == 'W') {
                // CONFIGURE PORT FOR WRITING: 'AW', 'BW', 'CW', 'DW'
                *(r + 1) = 0xFF;
                console__print_ok();
                console__println();
            }
            else if (c2 >= '0' && c2 <= '7') {
                // READ BIT: [A-D][0-7]
                uint8_t bit = c2 - '0';
                console__print_bool_as_0_or_1((*r) & (1 << bit));
                console__println();
            }
            else {
                console__print_error();
                console__println();
            }
        }
        else if (console__input_length == 3) {
            // CONFIGURE BIT: [A-D][0-7](R|W)
            uint8_t c2 = console__input_buffer[1];
            uint8_t c3 = console__input_buffer[2];

            if (c3 == 'R' || c3 == 'W') {
                if (c2 < '0' || c2 > '7') {
                    console__print_error();
                    console__println();
                    continue;
                }

                uint8_t bit = c2 - '0';
                if (c3 == 'R') {
                    // CONFIGURE BIT FOR READING: 'AnR', 'BnR', 'CnR', 'DnR'
                    *(r + 1) &= ~(1 << bit);
                    console__print_ok();
                    console__println();
                }
                else if (c3 == 'W') {
                    // CONFIGURE BIT FOR WRITING: 'AnW', 'BnW', 'CnW', 'DnW'
                    *(r + 1) |= (1 << bit);
                    console__print_ok();
                    console__println();
                }
            }
            else {
                if (c3 == '?') {
                    // READ MEMORY: AA?
                    uint16_t parsed_address = parser__parse_hex_byte(console__input_buffer);
                    if (!(parsed_address >> 8)) {
                        uint8_t address_byte = (uint8_t)(parsed_address & 0xFF);
                        uint8_t value = *((uint8_t*) address_byte);
                        console__print_byte_as_hex(value);
                        console__println();
                        continue;
                    }
                }
                console__print_error();
                console__println();
            }
        }
        else if (console__input_length == 4) {
            // WRITE BIT: [A-D][0-7]=[0-1]
            // WRITE BYTE: [A-D]=XX
            uint8_t c2 = console__input_buffer[1];
            if (c2 == '=') {
                // WRITE BYTE: [A-D]=XX
                uint16_t parsed_byte = parser__parse_hex_byte(console__input_buffer + 2);
                if (!(parsed_byte >> 8)) {
                    *(r + 2) = (uint8_t)(parsed_byte & 0xFF);
                    console__print_ok();
                    console__println();
                }
                else {
                    console__print_error();
                    console__println();
                }
            }
            else if (c2 >= '0' && c2 <= '7') {
                // WRITE BIT: [A-D][0-7]=[0-1]
                uint8_t c3 = console__input_buffer[2];
                if (c3 == '=') {
                    uint8_t bit = c2 - '0';
                    uint8_t c4 = console__input_buffer[3];
                    if (c4 == '0') {
                        *(r + 2) &= ~(1 << bit);
                        console__print_ok();
                        console__println();
                    }
                    else if (c4 == '1') {
                        *(r + 2) |= (1 << bit);
                        console__print_ok();
                        console__println();
                    }
                    else {
                        console__print_error();
                        console__println();
                    }
                }
                else {
                    console__print_error();
                    console__println();
                }
            }
            else {
                console__print_error();
                console__println();
            }
        } else if (console__input_length == 5) {
            // WRITE MEMORY: AA=XX
            uint8_t c3 = console__input_buffer[2];
            if (c3 == '=') {
                uint16_t parsed_address = parser__parse_hex_byte(console__input_buffer);
                uint16_t parsed_value = parser__parse_hex_byte(console__input_buffer + 3);
                if (!(parsed_address >> 8) && !(parsed_value >> 8)) {
                    *((uint8_t*) (uint8_t)(parsed_address & 0xFF)) = (uint8_t)(parsed_value & 0xFF);
                    console__print_ok();
                    console__println();
                }
                else {
                    console__print_error();
                    console__println();
                }
            }
            else {
                console__print_error();
                console__println();
            }
        }
    }
}
