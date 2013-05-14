#include "console_service.h"
#include "util/hex.h"

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/util/debug.h"


uint8_t console_service__command[16];
uint8_t console_service__command_length;


// Format: 'mXX?'
inline static uint8_t console_service__handle__memory_read(void) {
    if (console_service__command_length == 4 && console_service__command[0] == 'm' && console_service__command[3] == '?') {
        uint8_t addr = byte__parse_hex(console_service__command + 1);
        uint16_t addr16 = addr;

        register uint8_t v = *((uint8_t*)addr16);
        debug__print_byte_as_hex(addr);
        debug__putc('=');
        debug__print_byte_as_hex(v);
        return 1;
    }
    else return 0;
}


// Format: 'mXX=YY'
inline static bool console_service__handle__memory_write(void) {
    if (console_service__command_length == 6 && console_service__command[0] == 'm' && console_service__command[3] == '=') {
        register uint8_t addr = byte__parse_hex(console_service__command + 1);
        register uint8_t value = byte__parse_hex(console_service__command + 4);
        uint16_t addr16 = addr;
        *((uint8_t*)addr16) = value;    

        debug__putc('O');
        debug__putc('K');

        return true;
    }
    else return false;
}


// Format: 'cXX?'
inline static uint8_t console_service__handle__mcp2515_read_register(void) {
    if (console_service__command_length == 4 && console_service__command[0] == 'c' && console_service__command[3] == '?') {
        uint8_t addr = byte__parse_hex(console_service__command + 1);
        register uint8_t v;
        v = mcp251x__read(addr);
        debug__print_byte_as_hex(addr);
        debug__putc('=');
        debug__print_byte_as_hex(v);
        return 1;
    }
    else return 0;
}


// Format: 'cXX=YY'
inline static bool console_service__handle__mcp2515_write_register(void) {
    if (console_service__command_length == 6 && console_service__command[0] == 'c' && console_service__command[3] == '=') {
        register uint8_t addr = byte__parse_hex(console_service__command + 1);
        register uint8_t value = byte__parse_hex(console_service__command + 4);
            
        mcp251x__write(addr, value);

        debug__putc('O');
        debug__putc('K');

        return true;
    }
    else return false;
}


// Format: 'cr'
inline static bool console_service__handle__mcp2515_reset(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'c' && console_service__command[1] == 'r') {
        mcp251x__reset();
        return true;
    }
    else return false;
}


// Format: 'cs'
inline static bool console_service__handle__mcp2515_read_status(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'c' && console_service__command[1] == 's') {
        register uint8_t v;
        v = mcp2515__read_status();
        debug__print_byte_as_hex(v);
        return true;
    }
    else return false;
}


// Format: 'v1'
inline static bool console_service__handle__valve_on(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'v' && console_service__command[1] == '1') {
        out__water_valve__on();
        return true;
    }
    else return false;
}


// Format: 'v0'
inline static bool console_service__handle__valve_off(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'v' && console_service__command[1] == '0') {
        out__water_valve__off();
        return true;
    }
    else return false;
}

// Format: 'i1'
inline static bool console_service__handle__interrupts_enable(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'i' && console_service__command[1] == '1') {
        sei();
        return true;
    }
    else return false;
}

// Format: 'i0'
inline static bool console_service__handle__interrupts_disable(void) {
    if (console_service__command_length == 2 && console_service__command[0] == 'i' && console_service__command[1] == '0') {
        cli();
        return true;
    }
    else return false;
}


inline static void console_service__handle_command(void) {
    if (console_service__handle__memory_read()) return;
    if (console_service__handle__memory_write()) return;

    if (console_service__handle__mcp2515_read_status()) return;
    if (console_service__handle__mcp2515_read_register()) return;
    if (console_service__handle__mcp2515_write_register()) return;
    if (console_service__handle__mcp2515_reset()) return;

    if (console_service__handle__valve_off()) return;
    if (console_service__handle__valve_on()) return;

    if (console_service__handle__interrupts_enable()) return;
    if (console_service__handle__interrupts_disable()) return;

    debug__putc('?');
}



inline static void console_service__read_line(void) {
    uint8_t length = 0;
    while (1) {
        register uint8_t c = debug__in__read();

        if (c==13 || c==10) break;
        if (length < 16) console_service__command[length++] = c;
    }
    console_service__command_length = length;
}


void console_service__run(void) {
    while(1) {
        debug__putc('#');
        console_service__read_line();
        debug__putc(13);
        debug__putc(10);

        console_service__handle_command();
        debug__putc(13);
        debug__putc(10);
    }
}
