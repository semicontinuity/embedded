// =============================================================================
// The buttons scanner for 2 buttons at pins BUTTON1 and BUTTON2,
// all on the same BUTTONS__PORT.
// Does not support concurrent button presses.
// =============================================================================
#include "buttons_scanner.h"

struct buttons_scanner__status buttons_scanner__status = {
    .pins_changed       = 0,
    .pins_state	        = BUTTONS_MASK
};
