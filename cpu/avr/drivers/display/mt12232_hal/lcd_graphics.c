#include <stdint.h>
#include "cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h"


static uint8_t lcd_graphics__color;

/**
 * Sets drawing color (1 = black or other "active" color on monochrome display)
 */
void lcd_graphics__color__set(const uint8_t color) {
    lcd_graphics__color = color;
}

uint8_t lcd_graphics__color__is_active(void) {
    return lcd_graphics__color;
}


/**
 * Fill a rectangle at given coordinates with a previously specified color.
 * Helpers {@link #fill}, {@link #andWith}, {@link #orWith} are
 * not implemented with interface like in @{link BitBlt},
 * because their invocation does not require many ifs (at least now).
 * This is a low-level function, not an public-API function
 * (Assumes that all arguments are pre-checked, within allowed ranges)
 * @param x         x coordinate of left border
 * @param y         x coordinate of top border
 * @param width     width of rectangle
 * @param height    height of rectangle
 */
void lcd_graphics__fill_rect(
    const uint8_t x,
    const uint8_t y,
    const uint8_t width,
    const uint8_t height)
{
    uint8_t page = y >> 3U;
    const uint8_t topRowOffset = page << 3U;

    // Optionally paint "first" row
    // If y is not divisible by 8, the first row is painted specially
    // Also the first row can be the last one (all pixels touched lie within one row)
    // The bit mask should be specially calculated.
    const uint8_t start_offset_in_top_row = y - topRowOffset;
    const uint8_t end_offset_in_top_row = start_offset_in_top_row + height;
    if (start_offset_in_top_row > 0 || end_offset_in_top_row <= 7) {
        uint8_t mask = 0xFFU << start_offset_in_top_row;
        if (end_offset_in_top_row <= 7) {
            mask &= 0xFFU >> (8U - end_offset_in_top_row);
        }
        if (lcd_graphics__color__is_active()) {
            mt12232_hal__or_with(page, x, x + width, mask);
        } else {
            mt12232_hal__and_with(page, x, x + width, ~mask);
        }
        ++page;
    }

    // Paint "middle" rows - those completely filled
    // For this rows, appropriate bytes are simply filled with 0xFF or 0x00
    const uint8_t end_page = ((uint8_t)(y + height)) >> 3U;
    while (page < end_page) {
        mt12232_hal__fill_with(page, x, x + width, lcd_graphics__color__is_active() ? 0xFFU : 0x00U);
        ++page;
    }

    // Optionally paint "last" row
    // The bit mask should be specially calculated, depending on remaining_height
    const uint8_t remaining_height = y + height - (page << 3U);
    if (remaining_height > 0) {
        uint8_t mask = 0xFFU >> (8U - remaining_height);
        if (lcd_graphics__color__is_active()) {
            mt12232_hal__or_with(page, x, x + width, mask);
        } else {
            mt12232_hal__and_with(page, x, x + width, ~mask);
        }
    }
}


static uint8_t lcd_graphics__bit_blt_mask(uint8_t topBit, uint8_t bottomBit)
{
    return (0xFFU >> (8U - bottomBit)) & (0xFFU << topBit);
}

void lcd_graphics__bit_blt(
        uint8_t *src,
        const uint8_t srcStride,
        const uint8_t dstX,
        const uint8_t dstY,
        const uint8_t width,
        const uint8_t height)
{
    uint8_t page = dstY >> 3U;
    uint8_t toY = dstY + height;
    uint8_t finalPage = ((uint8_t)(toY - 1U)) >> 3U;

    // TODO optimize and make clear (e.g. with (x & 0xF8))
    uint8_t pivotBit = dstY - (page << 3U);
    uint8_t topShift = 8 - pivotBit;
    uint8_t bottomShift = pivotBit;

    while (page <= finalPage) {
        const int topBit = pivotBit;
        const int bottomBit = toY - (finalPage << 3U);

        if ((pivotBit == 0 || topBit < pivotBit) && topShift < 8) {
            mt12232_hal__blt_with_right_shift(
                    page, dstX, dstX + width, topShift,
                    lcd_graphics__bit_blt_mask(topBit, bottomBit > pivotBit ? pivotBit : bottomBit), 1U, src
            );
            src += srcStride;
        }
        if (bottomBit > pivotBit && pivotBit != 0) {
            mt12232_hal__blt_with_left_shift(
                    page, dstX, dstX + width, bottomShift,
                    lcd_graphics__bit_blt_mask(topBit, pivotBit < bottomBit ? pivotBit : bottomBit), 1U, src
            );
        }
        ++page;
    }
}
