// =============================================================================
// The scanner service for 2 buttons at pins BUTTON1 and BUTTON2.
// (The buttons must connected to the same port.)
// Does not support concurrent button presses.
// =============================================================================
#include "buttons_scanner.h"

struct buttons_scanner__status buttons_scanner__status = {
    .pins_changed       = 0,
    .pins_state	        = BUTTONS_MASK
};
