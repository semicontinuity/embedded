#ifndef SERVICES__SCANNER__BUTTON_LEDS_H
#define SERVICES__SCANNER__BUTTON_LEDS_H

#include "drivers/out/leds_rows.h"

void scanner__button_leds__init(void) {
    buttons__leds_row__init();
}

void scanner__button_leds__rewind(void);

void scanner__button_leds__render_column(uint8_t column, uint8_t phase);

#endif
