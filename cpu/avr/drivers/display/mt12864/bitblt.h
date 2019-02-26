// Source code adopted from electronix.ru
// --------------------------------------

#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12864__BITBLT_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12864__BITBLT_H

#include <avr/pgmspace.h>
#include <stdint.h>

#define   DRAW_DIRECT         0
#define   DRAW_XOR            (1 << 0)
#define   DRAW_INVERTED       (1 << 1)
#define   DRAW_UNDERLINED     (1 << 2)

// Draws bitmap from FLASH
void Draw_Bitmap(
    uint8_t X,
    uint8_t Y,
    uint8_t W,
    uint8_t H,
    const uint8_t *pData,
    uint8_t flags);


#endif