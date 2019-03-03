// =============================================================================
// Scanner (RGB LEDs).
// =============================================================================

#include "data.h"
#include "services/scanner__rgb_leds.h"
#include "cpu/avr/asm.h"


#ifdef SCANNER__RGB_LEDS__DATA_PTR__REG
register uint8_t *scanner__rgb_leds__data_ptr asm(QUOTE(SCANNER__RGB_LEDS__DATA_PTR__REG));
#else
volatile uint8_t *scanner__rgb_leds__data_ptr;
#endif


inline void scanner__rgb_leds__rewind(void) {
    scanner__rgb_leds__data_ptr = data__rgb_leds;
}


uint8_t scanner__rgb_leds__next_value(void) {
    uint8_t b;
#if defined(SCANNER__RGB_LEDS__DATA_PTR__REG) && SCANNER__RGB_LEDS__DATA_PTR__REG == 26
    b = LOAD_XPLUS(scanner__rgb_leds__data_ptr);
#elif defined(SCANNER__RGB_LEDS__DATA_PTR__REG) && SCANNER__RGB_LEDS__DATA_PTR__REG == 28
    b = LOAD_YPLUS(scanner__rgb_leds__data_ptr);
#elif defined(SCANNER__RGB_LEDS__DATA_PTR__REG) && SCANNER__RGB_LEDS__DATA_PTR__REG == 30
    b = LOAD_ZPLUS(scanner__rgb_leds__data_ptr);
#else
    b = *scanner__rgb_leds__data_ptr++;
#endif

    return b;
}

inline void scanner__rgb_leds__render_column(uint8_t phase) {
    led1r_row__set(0);
    if (scanner__rgb_leds__next_value() <= phase) {
        led1r_row__set(1);
    }

    led1g_row__set(0);
    if (scanner__rgb_leds__next_value() <= phase) {
        led1g_row__set(1);
    }

    led1b_row__set(0);
    if (scanner__rgb_leds__next_value() <= phase) {
        led1b_row__set(1);
    }

    led2r_row__set(0);
    if (scanner__rgb_leds__next_value() <= phase) {
        led2r_row__set(1);
    }

    led2g_row__set(0);
    if (scanner__rgb_leds__next_value() <= phase) {
        led2g_row__set(1);
    }

    led2b_row__set(0);
    if (scanner__rgb_leds__next_value() <= phase) {
        led2b_row__set(1);
    }
}
