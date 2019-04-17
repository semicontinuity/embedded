// =============================================================================
// I/O console.
//
// Supported commands:
//
// "B", "C", "D"
// =============================================================================

#include <avr/io.h>
#include <util/parser.h>
#include <stdlib.h>
#include "services/console_io.h"
#include "services/console.h"


uint8_t io__write_pin(volatile unsigned char *r, uint8_t bit_char, uint8_t value_char) {
    uint8_t bit = (uint8_t) (bit_char - '0');
    if (value_char == '0') {
        *(r + 2) &= ~(1 << bit);
        console__print_ok();
        console__println();
        return EXIT_SUCCESS;
    } else if (value_char == '1') {
        *(r + 2) |= (1 << bit);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}


uint8_t io__conf_pin(volatile unsigned char *r, uint8_t c2, uint8_t c3) {
    uint8_t bit = (uint8_t) (c2 - '0');
    if (c3 == 'R') {
        // CONFIGURE BIT FOR READING: 'BnR', 'CnR', 'DnR'
        *(r + 1) &= ~(1 << bit);
        console__print_ok();
        console__println();
        return EXIT_SUCCESS;
    } else if (c3 == 'W') {
        // CONFIGURE BIT FOR WRITING: 'BnW', 'CnW', 'DnW'
        *(r + 1) |= (1 << bit);
        console__print_ok();
        console__println();
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}


uint8_t console__io__run(void) {
    if (console__input_length == 0) {
        return EXIT_FAILURE;
    }

    volatile uint8_t *r;
    switch (console__input_buffer[0]) {
    case 'B': r = &PINB;
        break;
    case 'C': r = &PINC;
        break;
    case 'D': r = &PIND;
        break;
    default:
        return EXIT_FAILURE;
    }


    if (console__input_length == 1) {
        // READ BYTE: 'B', 'C', 'D'
        console__print_byte_as_hex(*r);
        console__println();
        return EXIT_SUCCESS;
    } else if (console__input_length == 2) {
        uint8_t c2 = console__input_buffer[1];
        if (c2 == 'R') {
            // CONFIGURE PORT FOR READING: 'BR', 'CR', 'DR'
            *(r + 1) = 0x00;
            console__print_ok();
            console__println();
            return EXIT_SUCCESS;
        } else if (c2 == 'W') {
            // CONFIGURE PORT FOR WRITING: 'BW', 'CW', 'DW'
            *(r + 1) = 0xFF;
            console__print_ok();
            console__println();
            return EXIT_SUCCESS;
        } else if (c2 >= '0' && c2 <= '7') {
            // READ BIT: [B-D][0-7]
            uint8_t bit = (uint8_t) (c2 - '0');
            console__print_bool_as_0_or_1((const uint8_t) ((*r) & (1 << bit)));
            console__println();
            return EXIT_SUCCESS;
        }
    } else if (console__input_length == 3) {
        // CONFIGURE BIT: [B-D][0-7](R|W)
        uint8_t c2 = console__input_buffer[1];
        uint8_t c3 = console__input_buffer[2];

        if (c2 >= '0' && c2 <= '7') {
            return io__conf_pin(r, c2, c3);
        }
    } else if (console__input_length == 4) {
        // WRITE BIT: [B-D][0-7]=[0-1]
        // WRITE BYTE: [B-D]=XX
        uint8_t c2 = console__input_buffer[1];
        if (c2 == '=') {
            // WRITE BYTE: [B-D]=XX
            uint16_t parsed_byte = parser__parse_hex_byte(console__input_buffer + 2);
            if (!(parsed_byte >> 8)) {
                *(r + 2) = (uint8_t) (parsed_byte & 0xFF);
                console__print_ok();
                console__println();
                return EXIT_SUCCESS;
            } 
        } else if (c2 >= '0' && c2 <= '7') {
            // WRITE BIT: [B-D][0-7]=[0-1]
            if (console__input_buffer[2] == '=') {
                io__write_pin(r, c2, console__input_buffer[3]);
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_FAILURE;
}
