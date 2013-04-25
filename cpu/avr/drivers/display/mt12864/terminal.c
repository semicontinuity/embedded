// Source code adopted from electronix.ru
// --------------------------------------

#include <avr/pgmspace.h>
#include "cpu/avr/drivers/display/mt12864/driver.h"
#include "cpu/avr/drivers/display/mt12864/char-output.h"
#include "util/font/Font_6x8.h"



uint8_t x = 0;     // in pixels
uint8_t y = 7;     // in pages, "page" in MT12868 is 8-pixel-high horizontal slice of screen, 8 "pages" in total.
uint8_t startPage = 0;


#define   setStartPage(startPage) { uint8_t cmd = MT12864_CMD_SET_DISPLAY_START_LINE((startPage) << 3); Write_Cmd_to_LCD(0, cmd); Write_Cmd_to_LCD(1, cmd); }


void terminal_feed(void) {
    x = 0;
    ++startPage;
    startPage &= 0x07;
    ++y;
    y &= 0x07;    
    setStartPage(startPage);

    // Установим страницу.
    Write_Cmd_Page_Addr_Set(0, y);
    Write_Cmd_Page_Addr_Set(1, y);
    // Очистим все столбцы страницы.
    Write_Cmd_Column_Addr_Set(0, 0);
    Write_Cmd_Column_Addr_Set(1, 0);
    Write_Data_to_LCD_n(0, (uint8_t)0x00, 64);
    Write_Data_to_LCD_n(1, (uint8_t)0x00, 64);
}


void terminal_displayChar(char c)
    if (c == 13) {
    }
    else if (c == 10) {
        terminal_feed();
    }
    else {
        if (x == 126) {
            terminal_feed();
        }
        Draw_Char(c, x, y<<3, &Font_6x8, 0);
        x+=6;
    }
}


void lcd_print_string_progmem(const char * PROGMEM str)
{
    for(;;)
    {
        uint8_t data = pgm_read_byte(str);
        if (data == 0) break;
        terminal_displayChar(data);
        str++;
    }
}
