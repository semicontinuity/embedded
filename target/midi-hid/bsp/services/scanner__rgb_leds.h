#ifndef SERVICES__SCANNER_H
#define SERVICES__SCANNER_H

#include "drivers/out/leds_rows.h"

void scanner__rgb_leds__init(void) {
    led1b_row__init();
    led1g_row__init();
    led1r_row__init();

    led2b_row__init();
    led2g_row__init();
    led2r_row__init();
}

void scanner__rgb_leds__rewind(void);

void scanner__rgb_leds__render_column(void);

#endif
