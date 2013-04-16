#include "console_service.h"
#include "parse.h"

#include "can_selector.h"

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/util/debug.h"
#include "cpu/avr/asm.h"


uint8_t console_service__command[16];
uint16_t console_service__command_length;


// Format: 'cXX?'
inline static bool console_service__handle__mcp2515_read_register(void) {
    if (console_service__command_length == 4 && console_service__command[0] == 'c' && console_service__command[3] == '?') {
        uint8_t addr = parseByte(console_service__command);
        register uint8_t v;
        can_selector__run(v = mcp251x_read_byte(addr));
        debug__print_byte_as_hex(v);
        return true;
    }
    else return false;
}


// Format: 'cXX=YY'
inline static bool console_service__handle__mcp2515_write_register(void) {
    if (console_service__command_length == 6 && console_service__command[0] == 'c' && console_service__command[3] == '=') {
        register uint8_t addr = parseByte(console_service__command);
        register uint8_t value = parseByte(console_service__command + 3);
            
        can_selector__run(mcp251x_write_one_byte(addr, value));
        return true;
    }
    else return false;
}


// Format: 'cr'
inline static bool console_service__handle__mcp2515_reset(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'c' && console_service__command[1] == 'r') {
        can_selector__run(mcp251x_reset());
        return true;
    }
    else return false;
}


inline static void console_service__handle_command(void) {
    if (console_service__handle__mcp2515_read_register()) return;
    if (console_service__handle__mcp2515_write_register()) return;
    if (console_service__handle__mcp2515_reset()) return;
}



inline static void console_service__read_line(void) {
    for(;;) {
        console_service__command_length = 0;
        register uint8_t c = debug__in__read();

        if (c==13 || c==10) break;
        if (console_service__command_length < 16) console_service__command[console_service__command_length++] = c;
    }
}


void console_service__run(void) {
    for(;;) {
        console_service__read_line();
        console_service__handle_command();
    }
}
