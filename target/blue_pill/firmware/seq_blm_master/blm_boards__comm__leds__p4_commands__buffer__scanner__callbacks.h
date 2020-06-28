#include <stdint.h>

/**
 * Callback function, invoked by the scanner, representing I2C command to be sent to a BLM board.
 */
void blm_boards__comm__leds__p4_commands__buffer__scanner__emit_command(uint8_t matrix, uint8_t command);
