#include "util/hex.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <stdint.h>


static inline void terminal__print_hex(const uint8_t v) {    
    const uint16_t s = byte__to_hex_string(v);
    terminal__putc(s >> 8);
    terminal__putc(s & 0xFF);
}

static uint8_t o[4];
static uint8_t i[4];

static void terminal__print_scan_result(const uint8_t column) {
    terminal__putc('\n');
    terminal__print_hex(o[column]);
    terminal__putc(' ');
    terminal__print_hex(i[column]);
}



inline void keypad__init(void) {
    DATA_DIR_REG(KEYPAD__OUT__PORT) |= ((1<<(KEYPAD__OUT__PIN+3)) | (1<<(KEYPAD__OUT__PIN+2)) | (1<<(KEYPAD__OUT__PIN+1)) | (1<<(KEYPAD__OUT__PIN+0)));
    PORT_REG(KEYPAD__IN__PORT) = ((1<<(KEYPAD__IN__PIN+3)) | (1<<(KEYPAD__IN__PIN+2)) | (1<<(KEYPAD__IN__PIN+1)) | (1<<(KEYPAD__IN__PIN+0))) | 4;
}

static inline void keypad__out(const uint8_t v) {
    OUT(KEYPAD__OUT, v);
}

static inline uint8_t keypad__in(void) { return PORT_VALUE(KEYPAD__IN); }


void keypad__scan_column(const uint8_t scanMask, const uint8_t column) __attribute__((noinline));
void keypad__scan_column(const uint8_t scanMask, const uint8_t column) {
    keypad__out(scanMask);
    o[column] = scanMask;

    uint8_t scanValue;
    scanValue = keypad__in();
    i[column] = scanValue;
}


INLINE void keypad__run(void) {
//    DATA_DIR_REG(KEYPAD__OUT__PORT) |= ((1<<(KEYPAD__OUT__PIN+3)) | (1<<(KEYPAD__OUT__PIN+2)) | (1<<(KEYPAD__OUT__PIN+1)) | (1<<(KEYPAD__OUT__PIN+0)));

    keypad__scan_column((uint8_t)~(1<<(KEYPAD__OUT__PIN)), 0);
    keypad__scan_column((uint8_t)~(1<<(KEYPAD__OUT__PIN+1)), 1);
    keypad__scan_column((uint8_t)~(1<<(KEYPAD__OUT__PIN+2)), 2);
    keypad__scan_column((uint8_t)~(1<<(KEYPAD__OUT__PIN+3)), 3);

    terminal__print_scan_result(0);
    terminal__print_scan_result(1);
    terminal__print_scan_result(2);
    terminal__print_scan_result(3);

//    DATA_DIR_REG(KEYPAD__OUT__PORT) &= ~((1<<(KEYPAD__OUT__PIN+3)) | (1<<(KEYPAD__OUT__PIN+2)) | (1<<(KEYPAD__OUT__PIN+1)) | (1<<(KEYPAD__OUT__PIN+0)));
}

// =============================================================================
// Application lifecycle
// =============================================================================

inline static void application__init(void) {
    // Drivers
    LCDG_InitPort();
    _delay_ms(30);  // takes longer?
    LCDG_InitLcd();
    LCDG_ClrAllDisp();

    terminal__init();
    keypad__init();
}

// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    application__init();

//    sei();
    for(;;) {
        keypad__run();
        _delay_ms(1000);
    }

    return 0;
}
