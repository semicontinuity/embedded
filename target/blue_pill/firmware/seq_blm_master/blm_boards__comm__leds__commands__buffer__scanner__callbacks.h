#include <stdint.h>

/**
 * Callback function, invoked by the scanner, representing I2C command to be sent to a BLM board.
 */
void blm_boards__comm__leds__commands__buffer__scanner__emit_command(uint8_t board, uint8_t command);
