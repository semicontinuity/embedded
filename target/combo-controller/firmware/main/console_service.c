#include "console_service.h"
#include "parse.h"

#include "can_selector.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/util/debug.h"


uint8_t console_service__command[16];
uint16_t input_length;


inline void console_service__read_line(void) {
    input_length=0;
    while (1) {
        register uint8_t c = debug__in__read();

        if (c==13 || c==10) break;
        if (input_length < 16) console_service__command[input_length++] = c;
    }
}


void console_service__run(void) {
    while(1) {
        debug__putc('>');
        debug__putc(13);
        debug__putc(10);

        console_service__read_line();

        if (input_length == 2) {
            uint8_t addr = parseByte(console_service__command);
            register uint8_t v;
            can_selector__run(v = mcp251x_read_byte(addr));

            debug__print_byte_as_hex(addr);
            debug__putc('=');
            debug__print_byte_as_hex(v);
        }
        else if (input_length == 5 && console_service__command[2] == '=') {

            register uint8_t addr = parseByte(console_service__command);
            register uint8_t value = parseByte(console_service__command + 3);
            
            can_selector__run(mcp251x_write_one_byte(addr, value));
            
        }
        else if (input_length == 1 && console_service__command[0] == 'r') {
            can_selector__run(mcp251x_reset());
        }
        debug__putc(13);
        debug__putc(10);
    }
}
