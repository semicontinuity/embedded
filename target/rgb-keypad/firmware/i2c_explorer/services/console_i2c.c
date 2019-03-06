#include "services/console_i2c.h"
#include "services/console.h"
#include "drivers/i2c_master.h"

#include <util/parser.h>
#include <stdlib.h>


#define CONSOLE__I2C__BUFFER_LENGTH 62
uint8_t console__i2c__buffer[CONSOLE__I2C__BUFFER_LENGTH];


void console__i2c__init(void) {
    i2c_init();
}

void dump(uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
            console__print_byte_as_hex(console__i2c__buffer[i]);
        }
}

/**
 * Supported commands:
 *
 * NN?LL
 *  Read LL bytes from device with address NN
 * NN=B0B1B2..BN
 *  Write bytes to device with address NN
 *
 * All numbers are in hex format
 */
uint8_t console__i2c__run(void) {
    if (console__input_length < 5) {
        return EXIT_FAILURE;
    }

    uint16_t parsed_address_byte = parser__parse_hex_byte(console__input_buffer);
    if ((uint8_t) (parsed_address_byte >> 8)) {
        return EXIT_FAILURE;
    }
    uint8_t address_byte = (uint8_t) parsed_address_byte;

    if (console__input_buffer[2] == '?' && console__input_length == 5) {
        uint16_t parsed_length_byte = parser__parse_hex_byte(console__input_buffer + 3);
        if ((uint8_t) (parsed_length_byte >> 8)) {
            return EXIT_FAILURE;
        }

        uint8_t length = (uint8_t) parsed_length_byte;

        if (i2c_start(address_byte)) {
            i2c_stop();
            return EXIT_FAILURE;
        }

        if (length > 0) {
            if (i2c_receive(address_byte, console__i2c__buffer, length)) {
                i2c_stop();
                return EXIT_FAILURE;
            }
        }

        i2c_stop();

        dump(length);
        console__println();

        return EXIT_SUCCESS;
    } else if (console__input_buffer[2] == '=') {
        if ((console__input_length & 1) == 0) {
            console__print('$');
            console__println();
            return EXIT_FAILURE;
        }

//        uint8_t *input_ptr = console__input_buffer + 3;
        uint8_t *bytes_ptr = console__i2c__buffer;
        uint8_t src_index = 3;
        for (;;) {
//            if (input_ptr >= console__input_buffer + console__input_length) break;
            if ((uint8_t) src_index >= (uint8_t) console__input_length) {
                console__print('!');
                console__println();
                break;
            }

//            uint8_t* p = &console__input_buffer[src_index];
            uint8_t c1 = console__input_buffer[src_index++];
            uint8_t c2 = console__input_buffer[src_index++];
            console__print(c1);
            console__print(c2);
            console__println();

            uint16_t parsed_byte = parser__parse_hex_chars(c1, c2);
            if ((uint8_t) (parsed_byte >> 8)) {
                console__print('P');
                console__println();
                return EXIT_FAILURE;
            }

            *bytes_ptr++ = (uint8_t) parsed_byte;
//            input_ptr += 2;
        }

        uint8_t length = (uint8_t) (src_index - 3);
        length = length >> 1;
        dump(length);

        if (i2c_start(address_byte)) {
            console__print('S');
            console__println();
            i2c_stop();
            return EXIT_FAILURE;
        }

        if (i2c_transmit(address_byte, console__i2c__buffer, length)) {
            console__print('T');
            console__println();
            i2c_stop();
            return EXIT_FAILURE;
        }

        i2c_stop();

        console__print_ok();
        console__println();
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
