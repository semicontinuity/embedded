// =============================================================================
// The driver for HD44780-based display.
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__HD44780__HD44780_H
#define __CPU__AVR__DRIVERS__DISPLAY__HD44780__HD44780_H


/** Initialize display */
void hd44780_lcd__init(void);

/** Place cursor at given coordinates */
void hd44780_lcd__goto(const uint8_t x, const uint8_t y);

/** Place character at current cursor position and shift cursor */
void hd44780_lcd__send_data(const uint8_t i);

/** Write string from given flash address to display at given coordinates */
void hd44780_lcd__write_string_xy_P(const char* p, uint8_t x, uint8_t y);

#define HD44780_LCD__COMMAND__CLEAR                 0x01
#define HD44780_LCD__COMMAND__USE_DDRAM             0x02
#define HD44780_LCD__COMMAND__SCREEN                0x04
#define HD44780_LCD__COMMAND__SCREEN_ADDRESS_INC    0x02
#define HD44780_LCD__COMMAND__SCREEN_ADDRESS_DEC    0x00
#define HD44780_LCD__COMMAND__DISPLAY               0x08
#define HD44780_LCD__COMMAND__DISPLAY_OFF           0x00
#define HD44780_LCD__COMMAND__DISPLAY_ON            0x04
#define HD44780_LCD__COMMAND__DISPLAY_CURSOR_OFF    0x00
#define HD44780_LCD__COMMAND__DISPLAY_CURSOR_ON     0x02
#define HD44780_LCD__COMMAND__DISPLAY_CURSOR_BLINK  0x01
#define HD44780_LCD__COMMAND__CONFIGURE             0x20
#define HD44780_LCD__COMMAND__CONFIGURE_BUS_4_BIT   0x00
#define HD44780_LCD__COMMAND__CONFIGURE_BUS_8_BIT   0x10
#define HD44780_LCD__COMMAND__CONFIGURE_LINES_1     0x00
#define HD44780_LCD__COMMAND__CONFIGURE_LINES_2     0x08
#define HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X8    0x00
#define HD44780_LCD__COMMAND__CONFIGURE_CHAR_5X10   0x04
#define HD44780_LCD__COMMAND__SET_DDRAM_ADDRESS     0x80

#define HD44780_LCD__LINE0_ADDRESS 0x00
#define HD44780_LCD__LINE1_ADDRESS 0x40
#define HD44780_LCD__LINE2_ADDRESS 0x14
#define HD44780_LCD__LINE3_ADDRESS 0x54

#endif