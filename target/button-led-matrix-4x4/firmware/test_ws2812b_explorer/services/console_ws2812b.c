// =============================================================================
// WS2812B console.
//
// Supported commands:
//
// "R":     refresh
// NN..NN   put binary data (parsed from hex string) to the buffer
// =============================================================================

#include <avr/io.h>
#include <stdlib.h>
#include "services/console_ws2812b.h"
#include "services/console.h"
#include "ws2812b_renderer.h"
#include <util/parser.h>



uint8_t console__ws2812b__run(void) {
    if (console__input_length == 0) {
        return EXIT_FAILURE;
    }

    if (console__input_length == 1 && console__input_buffer[0] == 'R') {
        ws2812b_renderer__start();
        return EXIT_SUCCESS;
    } else if ((console__input_length & 1) == 0) {
        uint8_t *bytes_ptr = ws2812b_renderer__data;
        uint8_t src_index = 0;
        for (;;) {
            if ((uint8_t) src_index >= (uint8_t) console__input_length) {
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
    }
    return EXIT_FAILURE;
}
