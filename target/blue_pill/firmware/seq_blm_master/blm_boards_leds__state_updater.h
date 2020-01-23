// Updates LED state data structures on LED update commands.
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_boards_leds.h"
#include "blm_boards_leds__state.h"


void blm_boards_leds__init() {
    for (int i = 0; i < 16; i++) {
        blm_boards_leds__state__current[i] = 0U;
    }
    for (int i = 0; i < 16; i++) {
        blm_boards_leds__state__requested[i] = 0U;
    }
    blm_boards_leds__state__dirty = 0U;
}


void debug_updater8(uint8_t param, uint8_t diff) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((diff >> 4) & 0x0F);
    Serial2.write(diff & 0x0F);
    Serial2.write(0xf7);
}

void debug_updater16(uint8_t param, uint16_t diff) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((diff >> 12) & 0x0F);
    Serial2.write((diff >> 8) & 0x0F);
    Serial2.write((diff >> 4) & 0x0F);
    Serial2.write(diff & 0x0F);
    Serial2.write(0xf7);
}

void debug_updater32(uint8_t param, uint32_t v) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((v >> 28) & 0x0F);
    Serial2.write((v >> 24) & 0x0F);
    Serial2.write((v >> 20) & 0x0F);
    Serial2.write((v >> 16) & 0x0F);
    Serial2.write((v >> 12) & 0x0F);
    Serial2.write((v >> 8) & 0x0F);
    Serial2.write((v >> 4) & 0x0F);
    Serial2.write(v & 0x0F);
    Serial2.write(0xf7);
}


void blm_boards_leds__update_one(
    uint8_t matrix_x,
    uint8_t matrix_y,
    uint8_t local_x,
    uint8_t local_y,
    uint8_t r,
    uint8_t g,
    uint8_t b)
{
    uint8_t matrix = (matrix_y << 2U) + matrix_x;
    debug_updater8(1, matrix);
    uint8_t led = (local_y << 2U) + local_x;
    debug_updater8(2, led);
    uint32_t requested = blm_boards_leds__state__requested[matrix];
    if (g) { requested |= (1U << led); } else { requested &= ~(1U << led);}
    if (r) { requested |= (1U << (led + 16U)); } else { requested &= ~(1U << (led + 16U));}

    debug_updater32(0x10, blm_boards_leds__state__current[matrix]);
    debug_updater32(0x11, requested);
    blm_boards_leds__state__requested[matrix] = requested;
    blm_boards_leds__state__dirty |= (1U << matrix);
    debug_updater16(0x18, blm_boards_leds__state__dirty);
}


void blm_boards_leds__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color) {
}


void blm_boards_leds__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color) {
}


void blm_boards_leds__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color) {
}


void blm_boards_leds__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color) {
}


void update_extra_leds(uint8_t is_second_half, uint8_t pattern, uint8_t color) {
}
