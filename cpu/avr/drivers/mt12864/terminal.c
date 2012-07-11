// Source code adopted from electronix.ru
// --------------------------------------

#include <avr/pgmspace.h>
#include "cpu/avr/drivers/mt12864/driver.h"
#include "cpu/avr/drivers/mt12864/char-output.h"
#include "util/font/Font_6x8.h"



uint8_t x = 0;     // in pixels
uint8_t y = 7;     // in pages, "page" in MT12868 is 8-pixel-high horizontal slice of screen, 8 "pages" in total.
uint8_t startPage = 0;


#define   setStartPage(startPage) { uint8_t cmd = MT12864_CMD_SET_DISPLAY_START_LINE((startPage) << 3); Write_Cmd_to_LCD(0, cmd); Write_Cmd_to_LCD(1, cmd); }

void terminal_displayChar(char c)
{
    // perhaps it's time to make a line feed
    if (x==126)
    {
        x = 0;
        ++startPage;
        if (startPage == 8) startPage = 0;
        ++y;
        if (y==8) y = 0;
    
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

    if (c==13)
    {
        // ignore
    }
    else if (c==10)
    {
        x = 126; // will feed the line
    }
    else
    {
        Draw_Char(c, x, y<<3, &Font_6x8, 0);
        x+=6;            
    }        
}