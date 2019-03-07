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


uint8_t console__i2c__read(uint8_t address_byte) {
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

    console__print_bytes_as_hex(console__i2c__buffer, length);
    console__println();

    return EXIT_SUCCESS;
}


uint8_t console__i2c__write(uint8_t address_byte) {
    uint8_t *bytes_ptr = console__i2c__buffer;
    uint8_t src_index = 3;
    for (;;) {
            if ((uint8_t) src_index >= (uint8_t) console__input_length) {
                console__print('!');
                console__println();
                break;
            }

            uint8_t c1 = console__input_buffer[src_index++];
            uint8_t c2 = console__input_buffer[src_index++];

            uint16_t parsed_byte = parser__parse_hex_chars(c1, c2);
            if ((uint8_t) (parsed_byte >> 8)) {
                return EXIT_FAILURE;
            }

            *bytes_ptr++ = (uint8_t) parsed_byte;
        }

    uint8_t length = (uint8_t) (src_index - 3);
    length = length >> 1;
    console__print_bytes_as_hex(console__i2c__buffer, length);

    if (i2c_start(address_byte)) {
            i2c_stop();
            return EXIT_FAILURE;
        }

    if (i2c_transmit(address_byte, console__i2c__buffer, length)) {
            i2c_stop();
            return EXIT_FAILURE;
        }

    i2c_stop();

    console__print_ok();
    console__println();
    return EXIT_SUCCESS;
}


/**
 * Supported commands:
 *
 * NN?LL
 *  Read LL bytes from I2C device with address NN
 * NN=B0B1B2..BN
 *  Write bytes to I2C device with address NN
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
        return console__i2c__read(address_byte);
    } else if (console__input_buffer[2] == '=' && (console__input_length & 1) != 0) {
        return console__i2c__write(address_byte);
    } else {
        return EXIT_FAILURE;
    }
}
