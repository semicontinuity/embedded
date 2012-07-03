#include "device.h"
#include "cpu/avr/util/debug.h"
#include "cpu/avr/usart0.h"

#include <stdint.h>
#include <avr/pgmspace.h>

// The user must define "debug__putc" that prints one character debug output

void debug__print_string_progmem(const char * PROGMEM str)
{
    for(;;)
    {
        uint8_t data = pgm_read_byte(str++);
        if (data == 0) break;
        debug__putc(data);
    }
}


// Prefer to spend flash and CPU, save RAM.
void debug__print_byte_as_hex(const uint8_t value)
{
    uint8_t temp1 = value >> 4;
    if (temp1 > 9) temp1 += ('A' - ('9' + 1));
    temp1 += '0';
    debug__putc (temp1);

    uint8_t temp2 = value & 0x0F;
    if (temp2 > 9) temp2 += ('A' - ('9' + 1));
    temp2 += '0';
    debug__putc (temp2);
}
