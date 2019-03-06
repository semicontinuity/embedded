#include "services/console_i2c.h"
#include "services/console.h"

#include <util/parser.h>
#include <stdlib.h>


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

    uint16_t parsed_byte = parser__parse_hex_byte(console__input_buffer);
    if (parsed_byte >> 8) {
        return EXIT_FAILURE;
    }

    if (console__input_buffer[2] == '?' && console__input_length == 5) {
        return EXIT_SUCCESS;
    } else if (console__input_buffer[2] == '=' && (console__input_length & 1)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
