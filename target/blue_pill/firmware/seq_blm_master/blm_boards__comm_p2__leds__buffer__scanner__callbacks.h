#include <stdint.h>

/**
 * Callback function, invoked by the scanner, representing I2C command to be sent to a BLM board.
 */
void blm_boards__comm_p2__leds__buffer__scanner__emit_command(uint8_t board, uint8_t command);
