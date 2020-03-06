#include <stdint.h>

/**
 * Callback function, invoked by the scanner, representing I2C command to be sent to a BLM board to update a row of LEDs
 */
void blm_boards__comm_p2__leds__buffer__scanner__update_row(
        uint8_t matrix,
        uint8_t row,
        uint8_t color_code,
        uint8_t pattern);

/**
 * Callback function, invoked by the scanner, representing I2C command to be sent to a BLM board to update a column of LEDs
 */
void blm_boards__comm_p2__leds__buffer__scanner__update_column(
        uint8_t matrix,
        uint8_t column,
        uint8_t color_code,
        uint8_t pattern);

