// Source code adopted from electronix.ru
// --------------------------------------

#ifndef __MT12864_BITBLT_H
#define __MT12864_BITBLT_H

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
    prog_uint8_t *pData,
    uint8_t flags);


#endif