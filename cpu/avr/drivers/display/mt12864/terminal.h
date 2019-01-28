// Source code adopted from electronix.ru
// --------------------------------------

#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12864__TERMINAL_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12864__TERMINAL_H

#include "cpu/avr/drivers/display/mt12864/driver.h"
#include <avr/pgmspace.h>


#define terminal_init() mt12864_init()

void terminal_displayChar(char c);

void lcd_print_string_progmem(const char * PROGMEM str);

#endif