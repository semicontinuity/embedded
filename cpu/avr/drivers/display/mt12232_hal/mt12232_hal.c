// =============================================================================
// HAL Driver for MT12232-type display.
// =============================================================================

#include "cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h"
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/gpio.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "drivers/out/lcd_backlight.h"


#define MT12232__COMMAND__SET_ADDRESS(a)    (0x00 + (a))
#define MT12232__COMMAND__SET_PAGE(p)       (0xb8 + (p))
#define MT12232__COMMAND__RMW               (0xe0)
#define MT12232__COMMAND__END               (0xee)


void mt12232_hal__write_data(const uint8_t value) {
    LCDG_SendData(value);
}

uint8_t mt12232_hal__read_data(void) {
    return LCDG_ReadData();
}

void mt12232_hal__page__set(const uint8_t page) {
    LCDG_SendCom(MT12232__COMMAND__SET_PAGE(page));
}

void mt12232_hal__chip__set(const uint8_t chip) {
    if (chip) OUT_0(MT12232__CS); else OUT_1(MT12232__CS);
}

void mt12232_hal__address__set(const uint8_t address) {
    LCDG_SendCom(MT12232__COMMAND__SET_ADDRESS(address));
}

void mt12232_hal__rmw__set(const uint8_t on) {
    LCDG_SendCom(on ? MT12232__COMMAND__RMW : MT12232__COMMAND__END);
}


void mt12232_hal__init(void) {
    LCDG_InitPort();
    _delay_ms(30);
    LCDG_InitLcd();
    LCDG_ClrAllDisp();
}


/** Copy a part of page (8-pixel-high strip) from RAM to LCD memory */
void mt12232_hal__copy(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t* data) {
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        for (; ;) {
            mt12232_hal__write_data(*data++);
            ++x;
            if (x >= x_limit) break;
        }
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);

        for (; ;) {
            mt12232_hal__write_data(*data++);
            ++x;
            if (x >= x_to) break;
        }
    }
}

/** Fill with mask a part of page (8-pixel-high strip) */
void mt12232_hal__fill_with(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t mask) {
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        for (; ;) {
            mt12232_hal__write_data(mask);
            ++x;
            if (x >= x_limit) break;
        }
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);

        for (; ;) {
            mt12232_hal__write_data(mask);
            ++x;
            if (x >= x_to) break;
        }
    }
}

/** AND with mask a part of page (8-pixel-high strip) */
void mt12232_hal__and_with(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t mask) {
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        for (; ;) {
            mt12232_hal__write_data(mt12232_hal__read_data() & mask);
            ++x;
            if (x >= x_limit) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        for (; ;) {
            mt12232_hal__write_data(mt12232_hal__read_data() & mask);
            ++x;
            if (x >= x_to) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
}

/** OR with mask a part of page (8-pixel-high strip) */
void mt12232_hal__or_with(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t mask) {
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        for (; ;) {
            mt12232_hal__write_data(mt12232_hal__read_data() | mask);
            ++x;
            if (x >= x_limit) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        for (; ;) {
            mt12232_hal__write_data(mt12232_hal__read_data() | mask);
            ++x;
            if (x >= x_to) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
}

__attribute__((noinline))
void mt12232_hal__blt_with_right_shift(
    const uint8_t page,
    const uint8_t x_from,
    const uint8_t x_to,
    const uint8_t shift,
    const uint8_t mask,
    const uint8_t set_bits_flag,
    volatile uint8_t *src)
{
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        __asm__ __volatile__("mt12232_hal__blt_with_right_shift_L1:");
        for (; ;) {
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_R1:");
            uint8_t read_value = mt12232_hal__read_data();
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_R2:");
            if (read_value) lcd_backlight__set(0);
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_R3:");

//            uint8_t new_value = (*src++) >> shift;
            uint8_t new_value = *src++;
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_R4:");
//            new_value &= mask;
//            new_value |= read_value;

//            if (set_bits_flag & 1U) { new_value &= mask; }
//            if (!(set_bits_flag & 1U)) { new_value |= mask; }
//            if (set_bits_flag & 1U) { new_value |= read_value; }
//            if (!(set_bits_flag & 1U)) { new_value &= read_value; }
//            mt12232_hal__write_data(((uint8_t)read_value) | (new_value & 0xFFU) );
//            mt12232_hal__write_data(new_value);
            mt12232_hal__write_data(read_value | new_value);
//            mt12232_hal__write_data(read_value);
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_W2:");
            ++x;
            if (x >= x_limit) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        for (; ;) {
            uint8_t new_value = (*src++) >> shift;
            uint8_t read_value = mt12232_hal__read_data();
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_2R4:");
            if (set_bits_flag & 1U) { new_value &= mask; }
            if (!(set_bits_flag & 1U)) { new_value |= mask; }
            if (set_bits_flag & 1U) { new_value |= read_value; }
            if (!(set_bits_flag & 1U)) { new_value &= read_value; }
            __asm__ __volatile__("mt12232_hal__blt_with_right_shift_2R5:");
            mt12232_hal__write_data(new_value);
            ++x;
            if (x >= x_to) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
}

void mt12232_hal__blt_with_left_shift(
        const uint8_t page,
        const uint8_t x_from,
        const uint8_t x_to,
        const uint8_t shift,
        const uint8_t mask,
        const uint8_t set_bits_flag,
        uint8_t *src)
{
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        for (; ;) {
            uint8_t new_value = (*src++) << shift;
            uint8_t read_value = mt12232_hal__read_data();
            if (set_bits_flag & 1U) { new_value &= mask; }
            if (!(set_bits_flag & 1U)) { new_value |= mask; }
            if (set_bits_flag & 1U) { new_value |= read_value; }
            if (!(set_bits_flag & 1U)) { new_value &= read_value; }
            mt12232_hal__write_data(new_value);
            ++x;
            if (x >= x_limit) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);
        mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
        mt12232_hal__read_data();       // according to the docs, must make dummy read

        for (; ;) {
            uint8_t new_value = (*src++) << shift;
            uint8_t read_value = mt12232_hal__read_data();
            if (set_bits_flag & 1U) { new_value &= mask; }
            if (!(set_bits_flag & 1U)) { new_value |= mask; }
            if (set_bits_flag & 1U) { new_value |= read_value; }
            if (!(set_bits_flag & 1U)) { new_value &= read_value; }
            mt12232_hal__write_data(new_value);
            ++x;
            if (x >= x_to) break;
        }
        mt12232_hal__rmw__set(0);   // turn off RMW, unfortunately, so it does not interfere with other commands
    }
}
