#include "services/console.h"
#include "util/hex.h"

#include "drivers/net/enc28j60.h"

#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/util/debug.h"

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


#include "spi.h"
#include "drivers/sdkarte/sd_raw.h"


uint8_t console__command[16];
uint8_t console__command_length;

uint8_t buffer[512];

/**
 * Initialize SDCARD
 * Command format: 'si'
 */
inline static bool console__handle__sd_init(void) {
    if (console__command_length == 2 && console__command[0] == 's' && console__command[1] == 'i') {
        spi_card_init();
        debug__print_byte_as_hex(sd_raw_init());
        return true;
    }
    else return false;
}

/**
 * SDCARD available
 * Command format: 'sa'
 */
inline static bool console__handle__sd_available(void) {
    if (console__command_length == 2 && console__command[0] == 's' && console__command[1] == 'a') {
        debug__print_byte_as_hex(sd_raw_available());
        return true;
    }
    else return false;
}

/**
 * SDCARD locked
 * Command format: 'sl'
 */
inline static bool console__handle__sd_locked(void) {
    if (console__command_length == 2 && console__command[0] == 's' && console__command[1] == 'l') {
        debug__print_byte_as_hex(sd_raw_locked());
        return true;
    }
    else return false;
}

/**
 * SDCARD read
 * Command format: 'sr'
 */
inline static bool console__handle__sd_read(void) {
    if (console__command_length == 2 && console__command[0] == 's' && console__command[1] == 'r') {
        debug__print_byte_as_hex(sd_raw_read(0, buffer, 512));

        debug__putc('\n');
        debug__putc('\r');
        uint8_t *b = buffer;
        for (uint8_t i = 0; i < 512/16; i++) {
            for (uint8_t j = 0; j < 16; j++) {
                debug__print_byte_as_hex(*b++);
                debug__putc(' ');
            }
            debug__putc('\n');
            debug__putc('\r');
        }
        return true;
    }
    else return false;
}


/**
 * Initialize ENC28J60
 * Command format: 'ei'
 */
inline static bool console__handle__enc28j60_init(void) {
    if (console__command_length == 2 && console__command[0] == 'e' && console__command[1] == 'i') {
        enc_init();
        return true;
    }
    else return false;
}


/**
 * Reset ENC28J60
 * Command format: 'er'
 */
inline static bool console__handle__enc28j60_reset(void) {
    if (console__command_length == 2 && console__command[0] == 'e' && console__command[1] == 'r') {
        enc_reset();
        return true;
    }
    else return false;
}


/**
 * Read register from ENC28J60
 * Command format: 'eXX?'
 */
inline static bool console__handle__enc28j60_read_register(void) {
    if (console__command_length == 4 && console__command[0] == 'e' && console__command[3] == '?') {
        register uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status1 = addr >> 8;
        if (status1) {
            debug__putc('!');
            return true;
        }

        register uint8_t v = enc_read_reg((uint8_t)addr);
        debug__print_byte_as_hex((uint8_t)addr);
        debug__putc('=');
        debug__print_byte_as_hex(v);
        return true;
    }
    else return false;
}


/**
 * Write register to ENC28J60
 * Command format: 'eXX=YY'
 */
inline static bool console__handle__enc28j60_write_register(void) {
    if (console__command_length == 6 && console__command[0] == 'e' && console__command[3] == '=') {
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
            
        enc_write_reg((uint8_t)addr, (uint8_t)value);
        debug__putc('O');
        debug__putc('K');
        return true;
    }
    else return false;
}


/**
 * Read phy register from ENC28J60
 * Command format: 'pXX?'
 */
inline static bool console__handle__enc28j60_read_phy_register(void) {
    if (console__command_length == 4 && console__command[0] == 'p' && console__command[3] == '?') {
        register uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status1 = addr >> 8;
        if (status1) {
            debug__putc('!');
            return true;
        }

        register uint16_t v = enc_read_phyreg((uint8_t)addr);
        debug__print_byte_as_hex((uint8_t)addr);
        debug__putc('=');
        debug__print_byte_as_hex(v >> 8);
        debug__print_byte_as_hex((uint8_t)v);
        return true;
    }
    else return false;
}


/**
 * Write phy register to ENC28J60
 * Command format: 'pXX=YYYY'
 */
inline static bool console__handle__enc28j60_write_phy_register(void) {
    if (console__command_length == 8 && console__command[0] == 'p' && console__command[3] == '=') {
        register uint16_t addr = byte__parse_hex(console__command + 1);
        uint8_t status1 = addr >> 8;
        if (status1) {
            debug__putc('!');
            return true;
        }

        register uint16_t h = byte__parse_hex(console__command + 4);
        uint8_t status_h = h >> 8;
        if (status_h) {
            debug__putc('!');
            return true;
        }

        register uint16_t l = byte__parse_hex(console__command + 6);
        uint8_t status_l = l >> 8;
        if (status_l) {
            debug__putc('!');
            return true;
        }

        register uint16_t value = (((uint8_t)h) << 8) | ((uint8_t)l);

        enc_write_phyreg((uint8_t)addr, value);
        debug__putc('O');
        debug__putc('K');
        return true;
    }
    else return false;
}


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


inline static void console__handle_command(void) {
    if (console__handle__enc28j60_init()) return;
    if (console__handle__enc28j60_reset()) return;
    if (console__handle__enc28j60_read_register()) return;
    if (console__handle__enc28j60_write_register()) return;
    if (console__handle__enc28j60_read_phy_register()) return;
    if (console__handle__enc28j60_write_phy_register()) return;

    if (console__handle__sd_available()) return;
    if (console__handle__sd_locked()) return;
    if (console__handle__sd_init()) return;
    if (console__handle__sd_read()) return;

    if (console__handle__memory_read()) return;

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
	// config enc chip select as output and deselect enc
	ENC_CS_DDR  |= (1<<ENC_CS);
	ENC_CS_PORT |= (1<<ENC_CS);

	// init spi
	//spi_init();

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
