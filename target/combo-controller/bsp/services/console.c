#include "services/console.h"
#include "util/hex.h"

#include "drivers/out/mcp251x_select.h"

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/util/debug.h"

#include "drivers/out/water_valve.h"

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


uint8_t console__command[16];
uint8_t console__command_length;


// Format: 'mXX?'
inline static bool console__handle__memory_read(void) {
    if (console__command_length == 4 && console__command[0] == 'm' && console__command[3] == '?') {
        uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status = addr >> 8;
        if (status) {
            debug__putc('!');
        }
        else {
            register uint8_t v = *((uint8_t*)addr);
            debug__print_byte_as_hex((uint8_t)addr);
            debug__putc('=');
            debug__print_byte_as_hex(v);
        }
        return true;
    }
    else return false;
}


// Format: 'mXX=YY'
inline static bool console__handle__memory_write(void) {
    if (console__command_length == 6 && console__command[0] == 'm' && console__command[3] == '=') {
        register uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status1 = addr >> 8;
        if (status1) {
            debug__putc('!');
            return true;
        }

        register uint16_t value = byte__parse_hex(console__command + 4);
        uint8_t status2 = value >> 8;
        if (status2) {
            debug__putc('!');
            return true;
        }

        *((uint8_t*)addr) = (uint8_t)value;
        debug__putc('O');
        debug__putc('K');
        return true;
    }
    else return false;
}


// Format: 'cXX?'
inline static bool console__handle__mcp2515_read_register(void) {
    if (console__command_length == 4 && console__command[0] == 'c' && console__command[3] == '?') {
        register uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status1 = addr >> 8;
        if (status1) {
            debug__putc('!');
            return true;
        }

        register uint8_t v;
        mcp251x_select__run(v = mcp251x__read((uint8_t)addr));
        debug__print_byte_as_hex((uint8_t)addr);
        debug__putc('=');
        debug__print_byte_as_hex(v);
        return true;
    }
    else return false;
}


// Format: 'cXX=YY'
inline static bool console__handle__mcp2515_write_register(void) {
    if (console__command_length == 6 && console__command[0] == 'c' && console__command[3] == '=') {
        register uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status1 = addr >> 8;
        if (status1) {
            debug__putc('!');
            return true;
        }

        register uint16_t value = byte__parse_hex(console__command + 4);
        uint8_t status2 = value >> 8;
        if (status2) {
            debug__putc('!');
            return true;
        }
            
        mcp251x_select__run(mcp251x__write((uint8_t)addr, (uint8_t)value));
        debug__putc('O');
        debug__putc('K');
        return true;
    }
    else return false;
}


// Format: 'cr'
inline static bool console__handle__mcp2515_reset(void) {
    if (console__command_length == 2 && console__command[0] == 'c' && console__command[1] == 'r') {
        mcp251x_select__run(mcp251x__reset());
        return true;
    }
    else return false;
}


// Format: 'cs'
inline static bool console__handle__mcp2515_read_status(void) {
    if (console__command_length == 2 && console__command[0] == 'c' && console__command[1] == 's') {
        register uint8_t v;
        mcp251x_select__run(v = mcp2515__read_status());
        debug__print_byte_as_hex(v);
        return true;
    }
    else return false;
}


// Format: 'v1'
inline static bool console__handle__valve_on(void) {
    if (console__command_length == 2 && console__command[0] == 'v' && console__command[1] == '1') {
        water_valve__on();
        return true;
    }
    else return false;
}


// Format: 'v0'
inline static bool console__handle__valve_off(void) {
    if (console__command_length == 2 && console__command[0] == 'v' && console__command[1] == '0') {
        water_valve__off();
        return true;
    }
    else return false;
}

// Format: 'i1'
inline static bool console__handle__interrupts_enable(void) {
    if (console__command_length == 2 && console__command[0] == 'i' && console__command[1] == '1') {
        sei();
        return true;
    }
    else return false;
}

// Format: 'i0'
inline static bool console__handle__interrupts_disable(void) {
    if (console__command_length == 2 && console__command[0] == 'i' && console__command[1] == '0') {
        cli();
        return true;
    }
    else return false;
}


inline static void console__handle_command(void) {
    if (console__handle__memory_read()) return;
    if (console__handle__memory_write()) return;

    if (console__handle__mcp2515_read_status()) return;
    if (console__handle__mcp2515_read_register()) return;
    if (console__handle__mcp2515_write_register()) return;
    if (console__handle__mcp2515_reset()) return;

    if (console__handle__valve_off()) return;
    if (console__handle__valve_on()) return;

    if (console__handle__interrupts_enable()) return;
    if (console__handle__interrupts_disable()) return;

    debug__putc('?');
}



inline static void console__read_line(void) {
    uint8_t length = 0;
    while (1) {
        register uint8_t c = debug__in__read();

        if (c==13 || c==10) break;
        if (length < 16) console__command[length++] = c;
    }
    console__command_length = length;
}


void console__run(void) {
    while(1) {
        debug__putc('#');
        console__read_line();
        debug__putc(13);
        debug__putc(10);

        console__handle_command();
        debug__putc(13);
        debug__putc(10);
    }
}
