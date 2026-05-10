#ifndef __FONT_5X8_H
#define __FONT_5X8_H

#include <stdint.h>
#include "cpu/memory.h"

extern const uint8_t PROGMEM Font_5x8[];

const uint8_t* PROGMEM Font_5x8__glyph_offset(char c);

const uint8_t Font_5x8__glyph_data(const uint8_t* PROGMEM offset);

#endif