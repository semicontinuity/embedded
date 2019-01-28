// Source code adopted from electronix.ru
// --------------------------------------

#include "cpu/avr/drivers/display/mt12864/char-output.h"
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
void Draw_Text(char *str, uint8_t X, uint8_t Y, struct FONT *font, uint8_t flags)
{
    // ��������������� ������� ������� ������ �� �������� �� ���������� (0x00).
    while(*str != 0)
    {
        // ������� ������� ������.
        Draw_Char(*str, X, Y, font, flags);
        str++;
        X += font->Width;
    }
}
