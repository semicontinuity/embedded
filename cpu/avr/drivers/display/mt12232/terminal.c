#include <avr/pgmspace.h>
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "util/font/Font_6x8.h"



uint8_t x = 0;     // in pixels
uint8_t y = 3;     // in pages, "page" is 8-pixel-high horizontal slice of screen, 4 "pages" in total.
uint8_t startPage = 0;


void terminal__feed(void) {
    x = 0;
    ++startPage;
    startPage &= 0x03;
    ++y;
    y &= 0x03;    

    unsigned char columnAddr;

    //  Chip 1  
    SetBit(PORT_LCD_CON, CS);
    LCDG_SendCom(COM_START_LINE((startPage) << 3));
    LCDG_SendCom(columnAddr);
    columnAddr = 0;
    do { LCDG_SendData(0); } while (++columnAddr < 61);

    //  Chip 2
    ClearBit(PORT_LCD_CON, CS); 
    LCDG_SendCom(COM_START_LINE((startPage) << 3));
    LCDG_SendCom(columnAddr);
    columnAddr = 0;
    do { LCDG_SendData(0); } while (++columnAddr < 61);
}


void terminal__putc(char c) {
    if (c == 13) {
    }
    else if (c == 10) {
        terminal__feed();
    }
    else {
        if (x == 20) {
            terminal__feed();
        }
        LCDG_SendSymbol(c, x, (y << 3));
        x++;
    }
}


void terminal__print_P(const char * PROGMEM str) {
    for(;;) {
        uint8_t data = pgm_read_byte(str);
        if (data == 0) break;
        terminal__putc(data);
        str++;
    }
}
