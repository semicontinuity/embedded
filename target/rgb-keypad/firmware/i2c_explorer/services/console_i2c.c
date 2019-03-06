#include "services/console_i2c.h"
#include "services/console.h"

#include <util/parser.h>
#include <stdlib.h>

#define CONSOLE__I2C__BUFFER_LENGTH 64
extern uint8_t console__i2c__buffer[CONSOLE__I2C__BUFFER_LENGTH];

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
        // TODO
        return EXIT_SUCCESS;
    } else if (console__input_buffer[2] == '=' && (console__input_length & 1)) {
        uint8_t *input_ptr = console__input_buffer + 3;
        uint8_t *bytes_ptr = console__input_buffer + 3;
        uint8_t length = 0;
        for (;;) {
            if (input_ptr >= console__input_buffer + console__input_length) break;

            uint16_t parsed_byte = parser__parse_hex_byte(console__input_buffer);
            if ((uint8_t) (parsed_byte >> 8)) {
                return EXIT_FAILURE;
            }

            *bytes_ptr++ = (uint8_t) parsed_byte;
            input_ptr += 2;
            ++length;
        }

        // TODO
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
