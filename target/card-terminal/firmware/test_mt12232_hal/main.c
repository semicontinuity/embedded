#include <util/delay.h>
#include "cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h"
#include "cpu/avr/drivers/display/mt12232_hal/lcd_graphics.h"

uint8_t buffer[122];

int main(int argc, char **argv) {
    mt12232_hal__init();

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

    lcd_graphics__color__set(LCD_GRAPHICS__COLOR__ACTIVE);
    lcd_graphics__fill_rect(0, 0, 122, 32);

    _delay_ms(200);

    lcd_graphics__color__set(LCD_GRAPHICS__COLOR__PASSIVE);
    lcd_graphics__fill_rect(1, 1, 120, 30);

    _delay_ms(200);

    lcd_graphics__color__set(LCD_GRAPHICS__COLOR__ACTIVE);
    lcd_graphics__fill_rect(2, 2, 118, 28);

    while(1);
    return 0;
}
