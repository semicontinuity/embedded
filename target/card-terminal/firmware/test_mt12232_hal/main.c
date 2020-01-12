#include <util/delay.h>
#include "drivers/out/lcd_backlight.h"
#include "cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h"
#include "cpu/avr/drivers/display/mt12232_hal/lcd_graphics.h"

uint8_t font[5] = {0x3E, 0x51, 0x49, 0x45, 0x3E};


void application__init(void) {
    lcd_backlight__init();
    mt12232_hal__init();
}


int main(void) __attribute__ ((naked));
int main(void) {
    application__init();

    lcd_backlight__set(1);

/*
    for (uint8_t i = 0; i < 122; i++) {
        buffer[i] = 0xAA;
    }
    mt12232_hal__copy(buffer, 0, 0, 61);
    mt12232_hal__copy(buffer, 1, 61, 122);
    mt12232_hal__copy(buffer, 2, 0, 122);
    mt12232_hal__copy(buffer, 3, 30, 92);
*/

//    mt12232_hal__or_with(0, 0, 122, 0xFF);
//    mt12232_hal__and_with(0, 0, 122, 0x18);

//    mt12232_hal__or_with(2, 0, 122, 0x55);

//    mt12232_hal__fill_with(0, 0, 122, 0xFF);
//    mt12232_hal__fill_with(1, 0, 122, 0xFF);
//    mt12232_hal__fill_with(2, 0, 122, 0xFF);
//    mt12232_hal__fill_with(3, 0, 122, 0xFF);

/*
    mt12232_hal__or_with(0, 0, 122, 0xFF);
    mt12232_hal__or_with(1, 0, 122, 0xFF);
    mt12232_hal__or_with(2, 0, 122, 0xFF);
    mt12232_hal__or_with(3, 0, 122, 0xFF);

    _delay_ms(200);

    mt12232_hal__and_with(0, 0, 122, 0x7E);
    mt12232_hal__and_with(1, 0, 122, 0x7E);
    mt12232_hal__and_with(2, 0, 122, 0x7E);
    mt12232_hal__and_with(3, 0, 122, 0x7E);

    _delay_ms(200);
*/

//    mt12232_hal__or_with(0, 0, 122, 0xFF);
//    mt12232_hal__or_with(1, 0, 122, 0xFF);
//    mt12232_hal__or_with(2, 0, 122, 0xFF);
//    mt12232_hal__or_with(3, 0, 122, 0xFF);

//    mt12232_hal__chip__set(0);
//    mt12232_hal__rmw__set(1);
//    mt12232_hal__chip__set(1);
//    mt12232_hal__rmw__set(1);

/*

    lcd_graphics__color__set(LCD_GRAPHICS__COLOR__ACTIVE);
    lcd_graphics__fill_rect(0, 0, 122, 32);

    _delay_ms(200);

    lcd_graphics__color__set(LCD_GRAPHICS__COLOR__PASSIVE);
    lcd_graphics__fill_rect(1, 1, 120, 30);

    _delay_ms(200);

    lcd_graphics__color__set(LCD_GRAPHICS__COLOR__ACTIVE);
    lcd_graphics__fill_rect(2, 2, 118, 28);
*/

/*
    mt12232_hal__copy(3, 0, 5, font);

    lcd_graphics__bit_blt(font, 5, 0x00, 0, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x08, 1, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x10, 2, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x18, 3, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x20, 4, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x28, 5, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x30, 6, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x38, 7, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x40, 8, 5, 8);
    lcd_graphics__bit_blt(font, 5, 0x48, 9, 5, 8);

    lcd_graphics__bit_blt(font, 5, 0x00, 10, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x08, 11, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x10, 12, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x18, 13, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x20, 14, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x28, 15, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x20, 16, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x28, 17, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x20, 18, 5, 4);
    lcd_graphics__bit_blt(font, 5, 0x28, 19, 5, 4);
*/

//    mt12232_hal__blt_with_right_shift(0, 0x00, 0x00 + 5, 0, 0xFF, 1, font);
//    mt12232_hal__blt_with_right_shift(0, 0x08, 0x08 + 5, 1, 0xFF, 1, font);
//    mt12232_hal__blt_with_right_shift(0, 0x10, 0x10 + 5, 2, 0xFF, 1, font);
//    mt12232_hal__blt_with_right_shift(0, 0x18, 0x18 + 5, 3, 0xFF, 1, font);

    uint8_t page = 0;
    uint8_t x = 0;
    uint8_t read_value;
    uint8_t new_value;

    mt12232_hal__chip__set(0);
    mt12232_hal__page__set(page);

    uint8_t address;
    address = x + 19;

    mt12232_hal__address__set(address);
    mt12232_hal__read_data();       // according to the docs, must make dummy read
//    mt12232_hal__rmw__set(1);   // according to the docs, many commands don't work when RMW is set, including PageSet
//    mt12232_hal__read_data();       // according to the docs, must make dummy read



    read_value = mt12232_hal__read_data();
    new_value = 0x3E;
    mt12232_hal__address__set(address);
    mt12232_hal__write_data(/*read_value | */new_value);
    ++address;
    _delay_ms(1);

    read_value = mt12232_hal__read_data();
    new_value = 0x51;
    mt12232_hal__address__set(address);
    mt12232_hal__write_data(/*read_value | */new_value);
    ++address;
    _delay_ms(1);

    read_value = mt12232_hal__read_data();
    new_value = 0x49;
    mt12232_hal__address__set(address);
    mt12232_hal__write_data(/*read_value | */new_value);
    ++address;
    _delay_ms(1);

    read_value = mt12232_hal__read_data();
    new_value = 0x45;
    mt12232_hal__address__set(address);
    mt12232_hal__write_data(/*read_value | */new_value);
    ++address;
    _delay_ms(1);

    read_value = mt12232_hal__read_data();
    new_value = 0x3e;
    mt12232_hal__address__set(address);
    mt12232_hal__write_data(/*read_value | */new_value);
    ++address;
    _delay_ms(1);

//    mt12232_hal__rmw__set(0);   // according to the docs, many commands don't work when RMW is set, including PageSet

    // ====================================================
    // Does not work as expected, with RMV flag or without.
    // Incorrect lib impl, timing?
    // Works as if value that is read pertains to previous address?
    // The first column of a symbol is rendered correctly,
    // but for the second, it should read 0 (nothing painted) and OR with new data, but non-zero value is read...
    //
    // perhaps, should write console app and experiment with reads/writes.
    // ====================================================


    while(1);
    return 0;
}
