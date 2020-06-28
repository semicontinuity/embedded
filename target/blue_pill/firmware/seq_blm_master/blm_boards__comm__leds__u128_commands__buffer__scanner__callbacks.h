#include <stdint.h>

/**
 * Callback function, invoked by the scanner, representing LED update to be sent to a BLM board.
 */
void blm_boards__comm__leds__u128_commands__buffer__scanner__emit_command(uint8_t matrix, uint8_t led, uint8_t color);
