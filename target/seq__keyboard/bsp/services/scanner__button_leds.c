// =============================================================================
// Scanner (Button LEDs).
// =============================================================================

#include "data.h"
#include "services/scanner__button_leds.h"
#include "drivers/out/leds_rows.h"


inline void scanner__button_leds__rewind(void) {
}



inline void scanner__button_leds__render_column(uint8_t column, uint8_t phase) {
    buttons__leds_row__set(0);

    if (column == 0) {
        if (data__button_leds & (1 << 0)) {
            buttons__leds_row__set(1);
        }
    }
    if (column == 1) {
        if (data__button_leds & (1 << 1)) {
            buttons__leds_row__set(1);
        }
    }
    if (column == 2) {
        if (data__button_leds & (1 << 2)) {
            buttons__leds_row__set(1);
        }
    }
    if (column == 3) {
        if (data__button_leds & (1 << 3)) {
            buttons__leds_row__set(1);
        }
    }
}
