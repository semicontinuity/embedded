// =============================================================================
// Nokia 5110 LCD driver.
//
// Notes:
//
// It seems, that display does not like to stay for long in DATA mode (DC=1),
// and the image disappears.
// Therefore, DATA mode is switched only for the time when pixels are sent.
// =============================================================================

#include "cpu/avr/gpio.h"
#include "soft_spi0.h"
#include <util/delay_basic.h>


#define LCD__COMMAND__EXT__CONTRAST (0x80)


void lcd__mode__data(void) {
    OUT_1(LCD__DC);
}

void lcd__mode__command(void) {
    OUT_0(LCD__DC);
}

void lcd__controller__on(void) {
    OUT_0(LCD__CE);
}

void lcd__controller__off(void) {
    OUT_1(LCD__CE);
}


void lcd__write(const uint8_t data) {
    lcd__controller__on();  // ?
    soft_spi0__write(data);
    lcd__controller__off(); // ?
}

void lcd__init(void) {
    ENABLE_PULLUP(LCD__RST);
    USE_AS_OUTPUT(LCD__RST);
    USE_AS_OUTPUT(LCD__DC);
    USE_AS_OUTPUT(LCD__CE);

    soft_spi0__init();

    _delay_loop_2(0);
    OUT_0(LCD__RST);
    _delay_loop_2(0);
    OUT_1(LCD__RST);

    lcd__controller__off();

    lcd__mode__command();
    lcd__write(0x21);   // Включаем расширенный набор команд (LCD Extended Commands)
    lcd__write(0xC8);   // Установка контрастности (LCD Vop)
    lcd__write(0x06);   // Установка температурного коэффициента (Temp coefficent)
    lcd__write(0x13);   // Настройка питания (LCD bias mode 1:48)
    lcd__write(0x20);   // Включаем стандартный набор команд и горизонтальную адресацию (LCD Standard Commands,Horizontal addressing mode)
    lcd__write(0x0C);   // Нормальный режим (LCD in normal mode)    
}

void lcd__extended_command_set(void) {
    lcd__write(0x21);
}

void lcd__standard_command_set(void) {
    lcd__write(0x20);
}

/**
 * Sets LCD contrast.
 * parameter value 0x00-0x7F
 */
void lcd__contrast(uint8_t value) {
    lcd__extended_command_set();
    lcd__write(LCD__COMMAND__EXT__CONTRAST | value);
    lcd__standard_command_set();
}


void lcd__x__set(const uint8_t x) {
    lcd__write(0x80 | x);
}

void lcd__bank__set(const uint8_t bank) {
    lcd__write(0x40 | bank);
}

void lcd__clear(void) {
    for (uint8_t j = 0; j < 6; j++) {
        lcd__mode__command();
        lcd__x__set(0);
        lcd__bank__set(j);
        lcd__mode__data();
        for (uint8_t i = 0; i < 84; i++) {
            lcd__write(0x00);
        }
    }
    lcd__mode__command();
}

#include "util/font/Font_5x8.h"

uint8_t lcd__terminal__column = 0;
uint8_t lcd__terminal__row = 0;


void lcd__terminal__reset(void) {
    lcd__x__set(0);
    lcd__bank__set(0);
}

void lcd__terminal__putch(char c) {
    lcd__mode__data();
    const uint8_t* PROGMEM glyph_offset = Font_5x8__glyph_offset(c);
    for (uint8_t i = 0; i < 5; i++) {
        lcd__write(Font_5x8__glyph_data(glyph_offset++));
    }
    
    lcd__write(0x00);
    lcd__mode__command();
    if (++lcd__terminal__column == 14) {
        lcd__terminal__column = 0;
        if (++lcd__terminal__row == 6) {
            lcd__terminal__row = 0;
        }
    }    
}

void lcd__terminal__line_feed(void) {
    lcd__mode__data();
    for (;;) {
        lcd__write(0x00);
        lcd__write(0x00);
        lcd__write(0x00);
        lcd__write(0x00);
        lcd__write(0x00);
        lcd__write(0x00);

        if (++lcd__terminal__column == 14) {
            lcd__terminal__column = 0;
            if (++lcd__terminal__row == 6) {
                lcd__terminal__row = 0;
            }
            break;
        }    
    }
    lcd__mode__command();
}
