// $Id$
/*
 * Application specific LCD driver for up to 4 HD44870 LCDs,
 * connected via individual, parallel 8-wire data + 3-wire control buses.
 * ==========================================================================
 * When no operations are performed with LCD at the moment:
 * RS must be set to 0 (command mode; don't remember why it was necessary),
 * RW must be set to 0 (write; don't remember why it was necessary),
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include "stm32fxxx_hal.h"
#include "tm_stm32_delay.h"
#include "tm_stm32_gpio.h"

#include "app_lcd.h"

uint32_t mios32_lcd_device = 0;
uint32_t mios32_lcd_column = 0;
uint32_t mios32_lcd_line = 0;

void select_lcd(uint32_t device) {
    mios32_lcd_device = device;
}

/////////////////////////////////////////////////////////////////////////////
// Pins
/////////////////////////////////////////////////////////////////////////////

struct hd44780_pins {
    GPIO_TypeDef *rs_port;
    GPIO_TypeDef *rw_port;
    GPIO_TypeDef *e_port;
    GPIO_TypeDef *data_port;
    uint16_t rs_pin_mask;
    uint16_t rw_pin_mask;
    uint16_t e_pin_mask;
    uint16_t data_pins_offset;
};

// 1-LCD Layout
static struct hd44780_pins displays[1] = {
    {
        .rs_port            = GPIOB,
        .rs_pin_mask        = GPIO_Pin_0,
        .rw_port            = GPIOB,
        .rw_pin_mask        = GPIO_Pin_1,
        .e_port             = GPIOB,
        .e_pin_mask         = GPIO_Pin_2,
        .data_port          = GPIOE,
        .data_pins_offset   = 8U,
    },
};


/////////////////////////////////////////////////////////////////////////////
// HD44780 stuff
//
// Write operation
//
// RS:
// --\/--------------------------\/-----
// --/\--------------------------/\-----
//
// RW:
// --\                            /-----
// ---\--------------------------/------
//   |  tAS  |
//
//               PWEH
//           +-------------+                +----------
// E:        |             |                |
// ----------+             +----------------+
//
// DATA:         |  tDSW   | tH  |
// -------------\/--------------\/-----
// -------------/\--------------/\-----
//
// tAS      address set-up time min 40nS
// tcycE    enable cycle time   min 500nS
// PWEH     enable pulse width  min 230nS
// tDSW     data set-up time    min 80nS
// tH       data hold time      min 10nS
/////////////////////////////////////////////////////////////////////////////

#define HD44780_LCD__DONT_USE_BUSY_FLAG             1

#define HD44780_LCD__BUSY_TIMEOUT_CYCLES            100
#define HD44780_LCD__ENABLE_PULSE_WIDTH_US          10
#define HD44780_LCD__ADDRESS_SETUP_TIME_US          1
#define HD44780_LCD__EXECUTION_DELAY_US             40

#define HD44780_LCD__COMMAND__CLEAR                 0x01U
/**
 * Return home sets DDRAM address 0 into the address counter,
 * and returns the display to its original status, if it was shifted. The DDRAM contents do not change.
 * Max execution time 1.52ms
 */
#define HD44780_LCD__COMMAND__RETURN_HOME           0x02U
#define HD44780_LCD__COMMAND__SCREEN                0x04U
#define HD44780_LCD__COMMAND__SCREEN_ADDRESS_INC    0x02U
#define HD44780_LCD__COMMAND__SCREEN_ADDRESS_DEC    0x00U
#define HD44780_LCD__COMMAND__DISPLAY               0x08U
#define HD44780_LCD__COMMAND__DISPLAY_OFF           0x00U
#define HD44780_LCD__COMMAND__DISPLAY_ON            0x04U
#define HD44780_LCD__COMMAND__DISPLAY_CURSOR_OFF    0x00U
#define HD44780_LCD__COMMAND__DISPLAY_CURSOR_ON     0x02U
#define HD44780_LCD__COMMAND__DISPLAY_CURSOR_BLINK  0x01U
#define HD44780_LCD__COMMAND__CONFIGURE             0x20U
#define HD44780_LCD__COMMAND__CONFIGURE_BUS_4_BIT   0x00U
#define HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT   0x10U
#define HD44780_LCD__COMMAND__CONFIGURE_LINES_1     0x00U
#define HD44780_LCD__COMMAND__CONFIGURE_LINES_2     0x08U
#define HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X8    0x00U
#define HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X10   0x04U
#define HD44780_LCD__COMMAND__SET_CGRAM_ADDRESS     0x40U
#define HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS     0x80U

#define HD44780_LCD__LINE0_ADDRESS 0x00U
#define HD44780_LCD__LINE1_ADDRESS 0x40U
#define HD44780_LCD__LINE2_ADDRESS 0x14U
#define HD44780_LCD__LINE3_ADDRESS 0x54U

/////////////////////////////////////////////////////////////////////////////
// Generic hd44780 support
/////////////////////////////////////////////////////////////////////////////

/**
 * Initializes Register Select (RS) pin as output.
 */
void hd44780_lcd__register_select__init(const struct hd44780_pins * const lcd) {
    TM_GPIO_Init(lcd->rs_port, lcd->rs_pin_mask, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
}

void hd44780_lcd__register_select__command(const struct hd44780_pins * const lcd) {
    TM_GPIO_SetPinLow(lcd->rs_port, lcd->rs_pin_mask);
}

void hd44780_lcd__register_select__data(const struct hd44780_pins * const lcd) {
    TM_GPIO_SetPinHigh(lcd->rs_port, lcd->rs_pin_mask);
}


/**
 * Initializes Read/Write (RW) pin as output.
 */
void hd44780_lcd__mode_init(const struct hd44780_pins * const lcd) {
    TM_GPIO_Init(lcd->rw_port, lcd->rw_pin_mask, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
}

void hd44780_lcd__mode_read(const struct hd44780_pins * const lcd) {
    TM_GPIO_SetPinHigh(lcd->rw_port, lcd->rw_pin_mask);
}

void hd44780_lcd__mode_write(const struct hd44780_pins * const lcd) {
    TM_GPIO_SetPinLow(lcd->rw_port, lcd->rw_pin_mask);
}


/**
 * Initializes Enable (E) pin as output.
 */
void hd44780_lcd__e__init(const struct hd44780_pins * const lcd) {
    TM_GPIO_Init(lcd->e_port, lcd->e_pin_mask, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
}

void hd44780_lcd__e_high(const struct hd44780_pins * const lcd) {
    TM_GPIO_SetPinHigh(lcd->e_port, lcd->e_pin_mask);
}

void hd44780_lcd__e_low(const struct hd44780_pins * const lcd) {
    TM_GPIO_SetPinLow(lcd->e_port, lcd->e_pin_mask);
}

void hd44780_lcd__latch_data(const struct hd44780_pins * const lcd) {
    hd44780_lcd__e_high(lcd);
    Delay(10);
    hd44780_lcd__e_low(lcd);
}


/**
 * Switches data pins to outputs.
 */
void hd44780_lcd__data_port__mode_write(const struct hd44780_pins * const lcd) {
    TM_GPIO_Init(lcd->data_port, 0xFFU << lcd->data_pins_offset, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
}

#if !defined(HD44780_LCD__DONT_USE_BUSY_FLAG) || HD44780_LCD__DONT_USE_BUSY_FLAG==0
/**
 * Switches data pins to inputs, with pull-ups.
 */
void hd44780_lcd__data_port__mode_read(const struct hd44780_pins * const lcd) {
    GPIO_InitTypeDef lcd0__GPIO_InitStructure;
    GPIO_StructInit(&lcd0__GPIO_InitStructure);
    lcd0__GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    lcd0__GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // weak driver to reduce transients
    lcd0__GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    lcd0__GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    lcd0__GPIO_InitStructure.GPIO_Pin = 0xFFU << lcd->data_pins_offset;
    GPIO_Init(lcd->data_port, &lcd0__GPIO_InitStructure);
}

/**
 * Switches data pins to inputs, without pull-ups.
 */
void hd44780_lcd__data_port__mode_hi(const struct hd44780_pins * const lcd) {
    GPIO_InitTypeDef lcd0__GPIO_InitStructure;
    GPIO_StructInit(&lcd0__GPIO_InitStructure);
    lcd0__GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    lcd0__GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // weak driver to reduce transients
    lcd0__GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    lcd0__GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    lcd0__GPIO_InitStructure.GPIO_Pin = 0xFFU << lcd->data_pins_offset;
    GPIO_Init(lcd->data_port, &lcd0__GPIO_InitStructure);
}
#endif

/**
 * Writes a byte of data to the data pins.
 */
void hd44780_lcd__data_port__write(const struct hd44780_pins *const lcd, const uint8_t value) {
    lcd->data_port->ODR = (uint16_t) (value << lcd->data_pins_offset)
        | (lcd->data_port->ODR & ~(0xFFU << lcd->data_pins_offset));
}

#if !defined(HD44780_LCD__DONT_USE_BUSY_FLAG) || HD44780_LCD__DONT_USE_BUSY_FLAG==0
uint8_t hd44780_lcd__is_busy(const struct hd44780_pins * const lcd) {
    return MIOS32_SYS_STM_PINGET(lcd->data_port, 1U << (lcd->data_pins_offset + 7U));
}


s32 hd44780_lcd__wait_until_not_busy(const struct hd44780_pins *const lcd, s32 time_out) {
    s32 result = -1;
    hd44780_lcd__data_port__mode_read(lcd);
    hd44780_lcd__mode_read(lcd);
    while (time_out > 0) {
        hd44780_lcd__e_high(lcd);
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");

        if (!hd44780_lcd__is_busy(lcd)) {
            time_out = 0;
            result = 0;
        }

        hd44780_lcd__e_low(lcd);
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");

        --time_out;
    }
    hd44780_lcd__mode_write(lcd);
    // data pins remain in read mode
    return result;
}
#endif

/**
 * Sends a byte to LCD.
 * If Busy flag is used, data pins are normally kept in high-Z mode, so need to switch to Output mode for the write.
 */
void hd44780_lcd__send_byte(const struct hd44780_pins * const lcd, const uint8_t i) {
#ifndef HD44780_LCD__DONT_USE_BUSY_FLAG
    hd44780_lcd__data_port__mode_write(lcd);
#endif
    hd44780_lcd__data_port__write(lcd, i);
    hd44780_lcd__latch_data(lcd);
#ifndef HD44780_LCD__DONT_USE_BUSY_FLAG
    hd44780_lcd__data_port__mode_hi(lcd);
#endif
}

s32 hd44780_lcd__send_command(const struct hd44780_pins * const lcd, const uint8_t i) {
#ifdef HD44780_LCD__DONT_USE_BUSY_FLAG
    Delay(40);
#else
    if (hd44780_lcd__wait_until_not_busy(lcd, HD44780_LCD__BUSY_TIMEOUT_CYCLES) < 0) return -1;
#endif
    hd44780_lcd__send_byte(lcd, i);
    return 0;
}

s32 hd44780_lcd__send_data(const struct hd44780_pins * const lcd, const uint8_t i) {
#ifdef HD44780_LCD__DONT_USE_BUSY_FLAG
    Delay(40);  // to complete previous operation, if any
#else
    if (hd44780_lcd__wait_until_not_busy(lcd, HD44780_LCD__BUSY_TIMEOUT_CYCLES) < 0) return -1;
#endif

    hd44780_lcd__register_select__data(lcd);
    Delay(1);
    hd44780_lcd__send_byte(lcd, i);
    hd44780_lcd__register_select__command(lcd);
    return 0;
}


void hd44780_lcd__init0(const struct hd44780_pins *const lcd) {
    hd44780_lcd__data_port__mode_write(lcd);
    hd44780_lcd__data_port__write(lcd, 0);

    hd44780_lcd__e__init(lcd);
    hd44780_lcd__e_low(lcd);

    hd44780_lcd__mode_init(lcd);
    hd44780_lcd__mode_write(lcd);

    hd44780_lcd__register_select__init(lcd);
    hd44780_lcd__register_select__command(lcd);
}

void hd44780_lcd__init1(const struct hd44780_pins *const lcd) {
    uint8_t i = 0;
    while (i < 30) {
        hd44780_lcd__data_port__write(lcd, HD44780_LCD__COMMAND__CONFIGURE | HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT);
        Delay(200);
        hd44780_lcd__latch_data(lcd);
        Delay(5000);
        i++;
    }
}

s32 hd44780_lcd__init2(const struct hd44780_pins * const lcd) {
    return hd44780_lcd__send_command(lcd, HD44780_LCD__COMMAND__CONFIGURE | HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT | HD44780_LCD__COMMAND__CONFIGURE_LINES_2 | HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X8);
}
s32 hd44780_lcd__init3(const struct hd44780_pins * const lcd) {
    return hd44780_lcd__send_command(lcd, HD44780_LCD__COMMAND__DISPLAY | HD44780_LCD__COMMAND__DISPLAY_ON | HD44780_LCD__COMMAND__DISPLAY_CURSOR_OFF);
}
s32 hd44780_lcd__init4(const struct hd44780_pins * const lcd) {
    return hd44780_lcd__send_command(lcd, HD44780_LCD__COMMAND__SCREEN | HD44780_LCD__COMMAND__SCREEN_ADDRESS_INC);
}
s32 hd44780_lcd__init5(const struct hd44780_pins * const lcd) {
    return hd44780_lcd__send_command(lcd, HD44780_LCD__COMMAND__RETURN_HOME);
}
s32 hd44780_lcd__init6(const struct hd44780_pins * const lcd) {
    return hd44780_lcd__send_command(lcd, HD44780_LCD__COMMAND__CLEAR);
}


s32 hd44780_lcd__init(const struct hd44780_pins * const lcd) {
    hd44780_lcd__init0(lcd);

    Delay(8000);

    hd44780_lcd__init1(lcd);

    Delay(8000);

    if (hd44780_lcd__init2(lcd) < 0) {
        return -1;
    }
    Delay(8000);
    if (hd44780_lcd__init3(lcd) < 0) {
        return -1;
    }
    Delay(8000);
    if (hd44780_lcd__init4(lcd) < 0) {
        return -1;
    }
    Delay(8000);
    if (hd44780_lcd__init5(lcd) < 0) {
        return -1;
    }

    // according to data sheet, max execution time of RETURN_HOME is 1.52ms

    Delay(8000);
    if (hd44780_lcd__init6(lcd) < 0) {
        return -1;
    }
    Delay(8000);
    return 0;
    // data pins will remain in high-Z mode (if using busy flag)
}


void hd44780_lcd__goto(const struct hd44780_pins * const lcd, const uint8_t x, const uint8_t y) {
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

    hd44780_lcd__send_command(lcd, command);
}


/////////////////////////////////////////////////////////////////////////////
// APP_LCD API implementation
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Initializes application specific LCD driver
// IN: <mode>: optional configuration
// OUT: returns < 0 if initialisation failed
/////////////////////////////////////////////////////////////////////////////
s32 APP_LCD_Init(u32 mode) {
    return hd44780_lcd__init(&displays[mios32_lcd_device]);
}


/////////////////////////////////////////////////////////////////////////////
// Sends data byte to LCD
// IN: data byte in <data>
// OUT: returns < 0 if display not available or timed out
/////////////////////////////////////////////////////////////////////////////
s32 APP_LCD_Data(u8 data) {
    return hd44780_lcd__send_data(&displays[mios32_lcd_device], data);
}


/////////////////////////////////////////////////////////////////////////////
// Sends command byte to LCD
// IN: command byte in <cmd>
// OUT: returns < 0 if display not available or timed out
/////////////////////////////////////////////////////////////////////////////
s32 APP_LCD_Cmd(u8 cmd) {
    return hd44780_lcd__send_command(&displays[mios32_lcd_device], cmd);
}


/////////////////////////////////////////////////////////////////////////////
// Clear Screen
// IN: -
// OUT: returns < 0 on errors
/////////////////////////////////////////////////////////////////////////////
s32 APP_LCD_Clear(void) {
    return hd44780_lcd__send_command(&displays[mios32_lcd_device], HD44780_LCD__COMMAND__CLEAR);
}


/////////////////////////////////////////////////////////////////////////////
// Sets cursor to given position
// IN: <column> and <line>
// OUT: returns < 0 on errors
/////////////////////////////////////////////////////////////////////////////
s32 APP_LCD_CursorSet(u16 column, u16 line) {
    hd44780_lcd__goto(&displays[mios32_lcd_device], column, line);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// Initializes a single special character
// IN: character number (0-7) in <num>, pattern in <table[8]>
// OUT: returns < 0 on errors
/////////////////////////////////////////////////////////////////////////////
s32 APP_LCD_SpecialCharInit(u8 num, u8 table[8]) {
    s32 i;

    // send command with CGRAM base address for given character
    APP_LCD_Cmd(((num & 7U) << 3U) | HD44780_LCD__COMMAND__SET_CGRAM_ADDRESS);

    // send 8 data bytes
    for (i = 0; i < 8; ++i)
        if (APP_LCD_Data(table[i]) < 0)
            return -1; // error during sending character

    // set cursor to original position
    return APP_LCD_CursorSet(mios32_lcd_column, mios32_lcd_line);
}
