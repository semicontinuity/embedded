// =============================================================================
// HAL Driver for MT12232-type display.
// =============================================================================

#include "cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h"
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/gpio.h"
#include <util/delay.h>
#include <avr/pgmspace.h>


#define MT12232__COMMAND__SET_ADDRESS(a)    (0x00 + (a))
#define MT12232__COMMAND__SET_PAGE(p)       (0xb8 + (p))


void mt12232_hal__send_data(const uint8_t value) {
    LCDG_SendData(value);
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


void mt12232_hal__init(void) {
    LCDG_InitPort();
    _delay_ms(30);
    LCDG_InitLcd();
    LCDG_ClrAllDisp();
}


/** Copy a part of page (8-pixel-high strip) from RAM to LCD memory */
void mt12232_hal__send_strip(const uint8_t* data, const uint8_t page, const uint8_t x_from, const uint8_t x_to) {
    uint8_t x = x_from;
    if (x_from < 61) {
        mt12232_hal__chip__set(0);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x + 19);

        uint8_t x_limit = x_to;
        if (x_limit > 61) x_limit = 61;

        for (; ;) {
            mt12232_hal__send_data(*data++);
            ++x;
            if (x >= x_limit) break;
        }
    }
    if (x_to > 61) {
        mt12232_hal__chip__set(1);
        mt12232_hal__page__set(page);
        mt12232_hal__address__set(x - 61);

        for (; ;) {
            mt12232_hal__send_data(*data++);
            ++x;
            if (x >= x_to) break;
        }
    }
}
