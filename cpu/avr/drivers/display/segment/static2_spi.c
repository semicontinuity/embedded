#include "cpu/avr/drivers/display/segment/static2_spi.h"
#include "cpu/avr/drivers/display/segment/glyphs.h"
#include "cpu/avr/drivers/display/segment/glyphs__digits.h"


INLINE void display__render_bcd(const uint8_t bcd) {
    display__set(((DIGITS[(bcd >> 4) & 0x0F]) << 8) | DIGITS[bcd & 0x0F]);
}
