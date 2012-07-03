#include "device.h"
#include "console_service.h"
#include "parse.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/mcp251x/operations.h"
#include "cpu/avr/util/debug.h"
#include "cpu/avr/usart0.h"


uint8_t input_buffer[16];
uint16_t input_length;

static void readLine (void)
{
    input_length=0;
    while(1)
    {
        register uint8_t c = usart__in__read();

        if (c==13 || c==10) break;
        if (input_length < 16) input_buffer[input_length++] = c;
    }
}


void console_service__run(void)
{
    while(1)
    {
        debug__putc('>');
        debug__putc(13);
        debug__putc(10);

        readLine();

        if (input_length == 2)
        {
//            debug__putc('>');
//            debug__putc('r');
//            debug__putc(13);
//            debug__putc(10);

            uint8_t addr = parseByte(input_buffer);
            
            DRIVE_LOW(SS);            
            register uint8_t v = mcp251x_read_byte(addr);
            DRIVE_HIGH(SS);            

//            debug__putc('<');
//            debug__putc('r');
//            debug__putc(13);
//            debug__putc(10);

            debug__print_byte_as_hex(addr);
            debug__putc('=');
            debug__print_byte_as_hex(v);
        }
        else if (input_length == 5 && input_buffer[2] == '=')
        {
//            debug__putc('>');
//            debug__putc('w');
//            debug__putc(13);
//            debug__putc(10);

            register uint8_t addr = parseByte(input_buffer);
            register uint8_t value = parseByte(input_buffer + 3);
            
            DRIVE_LOW(SS);            
            mcp251x_write_byte(addr, value);
            DRIVE_HIGH(SS);
            
//            debug__putc('<');
//            debug__putc('w');
//            debug__putc(13);
//            debug__putc(10);
        }
        else if (input_length == 1 && input_buffer[0] == 'r') {
//            debug__putc('>');
//            debug__putc('!');
//            debug__putc(13);
//            debug__putc(10);

            DRIVE_LOW(SS);            
            mcp251x_reset();
            DRIVE_HIGH(SS);

//            debug__putc('<');
//            debug__putc('!');
//            debug__putc(13);
//            debug__putc(10);
        }
        debug__putc(13);
        debug__putc(10);
    }
}
