// =============================================================================
// Nokia 5110 LCD driver.
// =============================================================================

#ifndef __NOKIA5110_H
#define __NOKIA5110_H

#include <stdint.h>

void lcd__mode__data(void);

void lcd__mode__command(void);

void lcd__write(const uint8_t data);

void lcd__init(void);

void lcd__clear(void);

void lcd__contrast(uint8_t value);

void lcd__terminal__reset(void);

void lcd__terminal__putch(char c);

#endif