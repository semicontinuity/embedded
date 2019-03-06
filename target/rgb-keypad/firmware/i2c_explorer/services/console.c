#include "drivers/i2c_master.h"
#include "services/console.h"
#include "util/parser.h"
#include "util/formatter.h"

#include <avr/interrupt.h>
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/drivers/usart0__tx.h"
#include "services/tx_ring_buffer.h"


uint8_t console__input_buffer[16];
uint16_t console__input_length;


void console__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();
}


inline void console__read_line(void) {
    console__input_length = 0;
    while (1) {
        uint8_t c = usart0__in__read();

        if (c==13 || c==10) break;
        if (console__input_length < 16) console__input_buffer[console__input_length++] = c;
    }
}

void console__print(const uint8_t c) {
    cli();
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(c);
    }
    sei();
}

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


void console__run(void) {
    console__read_line();
    if (console__input_length == 0) return;

    volatile uint8_t *r;
    switch (console__input_buffer[0]) {
    case 'B': r = &PINB;
        break;
    case 'C': r = &PINC;
        break;
    case 'D': r = &PIND;
        break;
    default:console__print_error();
        console__println();
        return;
    }


    if (console__input_length == 1) {
        // READ BYTE: 'B', 'C', 'D'
        console__print_byte_as_hex(*r);
        console__println();
    } else if (console__input_length == 2) {
        uint8_t c2 = console__input_buffer[1];
        if (c2 == 'R') {
            // CONFIGURE PORT FOR READING: 'BR', 'CR', 'DR'
            *(r + 1) = 0x00;
            console__print_ok();
            console__println();
        } else if (c2 == 'W') {
            // CONFIGURE PORT FOR WRITING: 'BW', 'CW', 'DW'
            *(r + 1) = 0xFF;
            console__print_ok();
            console__println();
        } else if (c2 >= '0' && c2 <= '7') {
            // READ BIT: [B-D][0-7]
            uint8_t bit = (uint8_t) (c2 - '0');
            console__print_bool_as_0_or_1((const uint8_t) ((*r) & (1 << bit)));
            console__println();
        } else {
            console__print_error();
            console__println();
        }
    } else if (console__input_length == 3) {
        // CONFIGURE BIT: [B-D][0-7](R|W)
        uint8_t c2 = console__input_buffer[1];
        uint8_t c3 = console__input_buffer[2];

        if (c2 < '0' || c2 > '7') {
            console__print_error();
            console__println();
            return;
        }

        uint8_t bit = (uint8_t) (c2 - '0');
        if (c3 == 'R') {
            // CONFIGURE BIT FOR READING: 'BnR', 'CnR', 'DnR'
            *(r + 1) &= ~(1 << bit);
            console__print_ok();
            console__println();
        } else if (c3 == 'W') {
            // CONFIGURE BIT FOR WRITING: 'BnW', 'CnW', 'DnW'
            *(r + 1) |= (1 << bit);
            console__print_ok();
            console__println();
        } else {
            console__print_bool_as_0_or_1((const uint8_t) ((*r) & (1 << bit)));
            console__println();
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
            } else {
                console__print_error();
                console__println();
            }
        } else if (c2 >= '0' && c2 <= '7') {
            // WRITE BIT: [B-D][0-7]=[0-1]
            uint8_t c3 = console__input_buffer[2];
            if (c3 == '=') {
                uint8_t bit = (uint8_t) (c2 - '0');
                uint8_t c4 = console__input_buffer[3];
                if (c4 == '0') {
                    *(r + 2) &= ~(1 << bit);
                    console__print_ok();
                    console__println();
                } else if (c4 == '1') {
                    *(r + 2) |= (1 << bit);
                    console__print_ok();
                    console__println();
                } else {
                    console__print_error();
                    console__println();
                }
            } else {
                console__print_error();
                console__println();
            }
        } else {
            console__print_error();
            console__println();
        }
    }
}


// =============================================================================
// Handlers
// =============================================================================

bool comm__tx__has_next(void) {
    return true; // interrupt triggered only if TX buffer is not empty
}

uint8_t comm__tx__next() {
    return tx_ring_buffer__get();
}

void comm__tx__on_done(void) {
    // never invoked
}
