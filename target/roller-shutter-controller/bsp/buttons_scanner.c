// =============================================================================
// The buttons scanner for 2 buttons at pins BUTTON1 and BUTTON2,
// all on the same BUTTONS__PORT.
// Does not support concurrent button presses.
// =============================================================================
#include "buttons_scanner.h"
#include <stdint.h>
#include <avr/io.h>
#include "cpu/avr/gpio.h"

uint8_t buttons_scanner__status[2] = {0, BUTTONS_MASK};
