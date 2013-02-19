#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/drivers/display/segment/values.h"

uint8_t const DIGITS[] = {
    DISPLAY_SEGMENT_VALUE_0,
    DISPLAY_SEGMENT_VALUE_1,
    DISPLAY_SEGMENT_VALUE_2,
    DISPLAY_SEGMENT_VALUE_3,
    DISPLAY_SEGMENT_VALUE_4,
    DISPLAY_SEGMENT_VALUE_5,
    DISPLAY_SEGMENT_VALUE_6,
    DISPLAY_SEGMENT_VALUE_7,
    DISPLAY_SEGMENT_VALUE_8,
    DISPLAY_SEGMENT_VALUE_9
};

INLINE void display__render_bcd(const uint8_t bcd) {
    display__set(((DIGITS[(bcd >> 4) & 0x0F]) << 8) | DIGITS[bcd & 0x0F]);
}
