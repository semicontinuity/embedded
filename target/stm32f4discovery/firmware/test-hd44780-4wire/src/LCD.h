#ifndef LCD_H
#define LCD_H

#include "stm32f4xx.h"

extern void lcd_init       (void);
extern void lcd_clear      (void);
extern void lcd_putchar    (char c);
extern void set_cursor     (int column, int line);
extern void lcd_print      (char *string);
extern void lcd_bargraph   (int value, int size);
extern void lcd_bargraphXY (int pos_x, int pos_y, int value);

#endif

