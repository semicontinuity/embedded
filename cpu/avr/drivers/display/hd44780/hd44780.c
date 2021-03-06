// =============================================================================
// Driver for HD44780-based display.
// =============================================================================

#include "cpu/avr/drivers/display/hd44780/hd44780.h"
#include "cpu/avr/gpio.h"
#include <util/delay.h>
#include <avr/pgmspace.h>


#if !defined(LCD__D4__PIN)
#error "Define LCD__D4__PIN"
#endif

#if !defined(LCD__D5__PIN)
#error "Define LCD__D5__PIN"
#endif

#if !defined(LCD__D6__PIN)
#error "Define LCD__D6__PIN"
#endif

#if !defined(LCD__D7__PIN)
#error "Define LCD__D7__PIN"
#endif


#if \
  defined(LCD__D0__PIN) && \
  defined(LCD__D1__PIN) && \
  defined(LCD__D2__PIN) && \
  defined(LCD__D3__PIN)

#  if !defined(LCD__DATA__PORT)
#    error "Define LCD__DATA__PORT"
#  endif

#  define HD44780_LCD__8_BIT_MODE
#  define LCD__D0__PORT LCD__DATA__PORT
#  define LCD__D1__PORT LCD__DATA__PORT
#  define LCD__D2__PORT LCD__DATA__PORT
#  define LCD__D3__PORT LCD__DATA__PORT

#else

#if defined(LCD__DATA__PORT)
#  define LCD__D4__PORT LCD__DATA__PORT
#  define LCD__D5__PORT LCD__DATA__PORT
#  define LCD__D6__PORT LCD__DATA__PORT
#  define LCD__D7__PORT LCD__DATA__PORT
#endif

#endif


void hd44780_lcd__e_high(void) {
    OUT_1(LCD__E);
}

void hd44780_lcd__e_low(void) {
    OUT_0(LCD__E);
}


void hd44780_lcd__register_select__command(void) {
    OUT_0(LCD__RES);
}

void hd44780_lcd__register_select__data(void) {
    OUT_1(LCD__RES);
}


void hd44780_lcd__latch_data(void) {
    hd44780_lcd__e_high();
    _delay_us(1);
    hd44780_lcd__e_low();
}


void hd44780_lcd__data_port__mode_hi(void) {
#ifdef HD44780_LCD__8_BIT_MODE
    USE_PORT_AS_INPUT(LCD__DATA);
    DISABLE_PULLUPS(LCD__DATA);
#else
    USE_AS_INPUT(LCD__D7);
    USE_AS_INPUT(LCD__D6);
    USE_AS_INPUT(LCD__D5);
    USE_AS_INPUT(LCD__D4);
    DISABLE_PULLUP(LCD__D7);
    DISABLE_PULLUP(LCD__D6);
    DISABLE_PULLUP(LCD__D5);
    DISABLE_PULLUP(LCD__D4);
#endif
}


void hd44780_lcd__data_port__write(const uint8_t value) {
    OUT(LCD__DATA, value);
}

void hd44780_lcd__data_port__mode_read(void) {
#ifdef HD44780_LCD__8_BIT_MODE
    USE_PORT_AS_INPUT(LCD__DATA);
    ENABLE_PULLUPS(LCD__DATA);
#else
    USE_AS_INPUT(LCD__D7);
    USE_AS_INPUT(LCD__D6);
    USE_AS_INPUT(LCD__D5);
    USE_AS_INPUT(LCD__D4);
    ENABLE_PULLUP(LCD__D7);
    ENABLE_PULLUP(LCD__D6);
    ENABLE_PULLUP(LCD__D5);
    ENABLE_PULLUP(LCD__D4);
#endif
}


void hd44780_lcd__data_port__mode_write(void) {
#if defined(HD44780_LCD__8_BIT_MODE)
    USE_PORT_AS_OUTPUT(LCD__DATA);
    OUT(LCD__DATA, 0x00);
#else
    USE_AS_OUTPUT(LCD__D7);
    USE_AS_OUTPUT(LCD__D6);
    USE_AS_OUTPUT(LCD__D5);
    USE_AS_OUTPUT(LCD__D4);
    OUT_0(LCD__D7);
    OUT_0(LCD__D6);
    OUT_0(LCD__D5);
    OUT_0(LCD__D4);
#endif
}


void hd44780_lcd__mode_read(void) {
    OUT_1(LCD__RW);
}

void hd44780_lcd__mode_write(void) {
    OUT_0(LCD__RW);
}


uint8_t hd44780_lcd__is_busy(void) {
    return IS_1(LCD__D7);
}

void hd44780_lcd__wait_until_not_busy(void) {
    hd44780_lcd__data_port__mode_read();
    hd44780_lcd__mode_read();
    uint8_t i = 1;
    while (i == 1) {
        hd44780_lcd__e_high();
        asm("nop");
        asm("nop");
        if (!hd44780_lcd__is_busy()) {
            i = 0;
        }
        hd44780_lcd__e_low();
        asm("nop");
        asm("nop");
#if !defined(HD44780_LCD__8_BIT_MODE)
        hd44780_lcd__latch_data();
        asm("nop");
        asm("nop");
#endif
    }
    hd44780_lcd__mode_write();
}


void hd44780_lcd__send_byte(const uint8_t i) {
    hd44780_lcd__data_port__mode_write();   // output 0 at data port, some 0s excessive, can be optimized

#ifdef HD44780_LCD__8_BIT_MODE
/*
    if (i & (1 << 0)) {
        OUT_1(LCD__D0);
    }
    else {
        OUT_0(LCD__D0);
    }

    if (i & (1 << 1)) {
        OUT_1(LCD__D1);
    }
    if (!(i & (1 << 1))) {
        OUT_0(LCD__D1);
    }

    if (i & (1 << 2)) {
        OUT_1(LCD__D2);
    }
    if (!(i & (1 << 2))) {
        OUT_0(LCD__D2);
    }

    if (i & (1 << 3)) {
        OUT_1(LCD__D3);
    }
    if (!(i & (1 << 3))) {
        OUT_0(LCD__D3);
    }

    if (i & (1 << 4)) {
        OUT_1(LCD__D4);
    }
    if (!(i & (1 << 4))) {
        OUT_0(LCD__D4);
    }

    if (i & (1 << 5)) {
        OUT_1(LCD__D5);
    }
    if (!(i & (1 << 5))) {
        OUT_0(LCD__D5);
    }

    if (i & (1 << 6)) {
        OUT_1(LCD__D6);
    }
    if (!(i & (1 << 6))) {
        OUT_0(LCD__D6);
    }

    if (i & (1 << 7)) {
        OUT_1(LCD__D7);
    }
    if (!(i & (1 << 7))) {
        OUT_0(LCD__D7);
    }
*/
    OUT(LCD__DATA, i);
#else

    uint8_t h = ((i & 0b11110000) >> 4);
    uint8_t l = (i & 0b00001111);

    if ((h & 1) == 1) {
        OUT_1(LCD__D4);
    }
    h = h >> 1;
    if ((h & 1) == 1) {
        OUT_1(LCD__D5);
    }
    h = h >> 1;
    if ((h & 1) == 1) {
        OUT_1(LCD__D6);
    }
    h = h >> 1;
    if ((h & 1) == 1) {
        OUT_1(LCD__D7);
    }

    hd44780_lcd__latch_data();
    hd44780_lcd__data_port__mode_write();   // output 0 at data port, some 0s excessive, can be optimized

    if ((l & 1) == 1) {
        OUT_1(LCD__D4);
    }
    l = l >> 1;
    if ((l & 1) == 1) {
        OUT_1(LCD__D5);
    }
    l = l >> 1;
    if ((l & 1) == 1) {
        OUT_1(LCD__D6);
    }
    l = l >> 1;
    if ((l & 1) == 1) {
        OUT_1(LCD__D7);
    }
#endif

    hd44780_lcd__latch_data();
    hd44780_lcd__data_port__mode_hi();
}


void hd44780_lcd__send_command(const uint8_t i) {
    hd44780_lcd__wait_until_not_busy();
    hd44780_lcd__send_byte(i);
}


void hd44780_lcd__send_data(const uint8_t i) {
    hd44780_lcd__wait_until_not_busy();
    hd44780_lcd__register_select__data();
    hd44780_lcd__send_byte(i);
    hd44780_lcd__register_select__command();
}


/** Initialize display I/O pins */
void hd44780_lcd__init_io(void) {
#if defined(HD44780_LCD__8_BIT_MODE)
    USE_AS_OUTPUT(LCD__D0);
    USE_AS_OUTPUT(LCD__D1);
    USE_AS_OUTPUT(LCD__D2);
    USE_AS_OUTPUT(LCD__D3);
#endif
    USE_AS_OUTPUT(LCD__D4);
    USE_AS_OUTPUT(LCD__D5);
    USE_AS_OUTPUT(LCD__D6);
    USE_AS_OUTPUT(LCD__D7);
    USE_AS_OUTPUT(LCD__RES);
    USE_AS_OUTPUT(LCD__RW);
    USE_AS_OUTPUT(LCD__E);
}

/** Initialize display */
void hd44780_lcd__init(void) {
    hd44780_lcd__init_io();
    _delay_ms(100);
    hd44780_lcd__e_low();
    hd44780_lcd__mode_write();
    hd44780_lcd__register_select__command();
    hd44780_lcd__data_port__mode_write();

    uint8_t i = 0;
    while (i != 3) {
#if defined(HD44780_LCD__8_BIT_MODE)
        hd44780_lcd__data_port__write(HD44780_LCD__COMMAND__CONFIGURE | HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT);
#else
        // high(HD44780_LCD__COMMAND__CONFIGURE | HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT) = high (0x30) = 0x3 at D7:D4
        OUT_1(LCD__D5);
        OUT_1(LCD__D4);
#endif

        hd44780_lcd__latch_data();
        _delay_ms(5);
        i++;
    }

#if defined(HD44780_LCD__8_BIT_MODE)
    hd44780_lcd__send_command(
        HD44780_LCD__COMMAND__CONFIGURE |
        HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT |
        HD44780_LCD__COMMAND__CONFIGURE_LINES_2 |
        HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X8
    );
#else
    // send high 4 buts first
    hd44780_lcd__wait_until_not_busy();
    hd44780_lcd__data_port__mode_write();

    // 4-bit interface
    // high(HD44780_LCD__COMMAND__CONFIGURE | HD44780_LCD__COMMAND__CONFIGURE_BUS_4_BIT) = high (0x30) = 0x3 at D7:D4
    OUT_0(LCD__D7);
    OUT_0(LCD__D6);
    OUT_1(LCD__D5);
    OUT_0(LCD__D4);

    hd44780_lcd__latch_data();

    hd44780_lcd__send_command(
        HD44780_LCD__COMMAND__CONFIGURE |
        HD44780_LCD__COMMAND__CONFIGURE_BUS_4_BIT |
        HD44780_LCD__COMMAND__CONFIGURE_LINES_2 |
        HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X8
    );
#endif

    hd44780_lcd__send_command(HD44780_LCD__COMMAND__DISPLAY | HD44780_LCD__COMMAND__DISPLAY_ON | HD44780_LCD__COMMAND__DISPLAY_CURSOR_OFF);
    hd44780_lcd__send_command(HD44780_LCD__COMMAND__SCREEN | HD44780_LCD__COMMAND__SCREEN_ADDRESS_INC);
    hd44780_lcd__send_command(HD44780_LCD__COMMAND__USE_DDRAM);
    hd44780_lcd__send_command(HD44780_LCD__COMMAND__CLEAR);
}


void hd44780_lcd__goto(const uint8_t x, const uint8_t y) {
    uint8_t command;
    switch (y) {
    case 0: command = (HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS | HD44780_LCD__LINE0_ADDRESS) + x;
        break;
    case 1: command = (HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS | HD44780_LCD__LINE1_ADDRESS) + x;
        break;
    case 2: command = (HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS | HD44780_LCD__LINE2_ADDRESS) + x;
        break;
    case 3: command = (HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS | HD44780_LCD__LINE3_ADDRESS) + x;
        break;
    default: command = (HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS | HD44780_LCD__LINE0_ADDRESS) + x;
    }

    hd44780_lcd__send_command(command);
}

void hd44780_lcd__write_string_xy_P(const char* p, const uint8_t x, const uint8_t y) {
    hd44780_lcd__goto(x, y);
    for (uint8_t i = 0; ; i++) {
        uint8_t b = (uint8_t) pgm_read_byte(&p[i]);
        if (!b) break;
        hd44780_lcd__send_data(b);
    }
}
