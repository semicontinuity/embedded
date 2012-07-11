#include <avr/pgmspace.h>
#include "terminal.h"

void lcd_print_string_progmem(const char *str)
{
    for(;;)
    {
        uint8_t data = pgm_read_byte(str);
        if (data == 0) break;
        terminal_displayChar(data);
        str++;
    }
}
