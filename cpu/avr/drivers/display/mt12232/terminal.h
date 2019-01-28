#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12232__TERMINAL_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12232__TERMINAL_H

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include <avr/pgmspace.h>


inline void terminal__init(void) {
    SetBit(PORT_LCD_CON, CS);
    LCDG_SendCom(COM_START_LINE(0));

    ClearBit(PORT_LCD_CON, CS); 
    LCDG_SendCom(COM_START_LINE(0));

}


void terminal__putc(char c);

void terminal__print_P(const char * PROGMEM str);

#endif