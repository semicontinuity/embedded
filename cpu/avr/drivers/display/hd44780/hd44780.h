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

#define HD44780_LCD__LINE0 0x80
#define HD44780_LCD__LINE1 0xc0
#define HD44780_LCD__LINE2 0x94
#define HD44780_LCD__LINE3 0xd4

#endif