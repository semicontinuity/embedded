#define LCD_GRAPHICS__COLOR__ACTIVE     (1)
#define LCD_GRAPHICS__COLOR__PASSIVE    (0)

/**
 * Sets drawing color (1 = black or other "active" color on monochrome display)
 */
void lcd_graphics__color__set(const uint8_t color);

/**
 * Fill a rectangle at given coordinates with a previously specified color.
 * Assumes that all arguments are pre-checked, within allowed ranges.
 * @param x         x coordinate of left border
 * @param y         x coordinate of top border
 * @param width     width of rectangle
 * @param height    height of rectangle
 */
void lcd_graphics__fill_rect(const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t height);