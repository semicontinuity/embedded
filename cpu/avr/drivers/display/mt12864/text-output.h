// Source code adopted from electronix.ru
// --------------------------------------

#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12864__TEXT_OUTPUT_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12864__TEXT_OUTPUT_H

#include "util/font/fixed-width-font.h"
#include <stdint.h>

/**
 * Draw text with a given font at given coordinates
 * @param str
 * @param X     X coordinate in pixels
 * @param Y     Y coordinate in pixels
 * @param font  font to use
 * @param flags flags
 */
void Draw_Text(char *str, uint8_t X, uint8_t Y, struct FONT *font, uint8_t flags);


#endif