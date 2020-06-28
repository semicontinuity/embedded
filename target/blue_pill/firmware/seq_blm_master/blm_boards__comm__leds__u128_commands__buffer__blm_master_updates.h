// Implements updating of multi-BLM LEDs UNPACK128 commands buffer
// for blm_master-style commands.
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"
#include "blm_boards__comm__leds__u128_commands__buffer.h"


/**
 * @param color_code 00..1f: black; 20..3f: green; 40..5f red; 60..7f yellow
 */
void blm_boards__comm__leds__commands__buffer__blm_master__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_ONE);
    uint8_t matrix_x = ((uint8_t)(column >> 2U)) & 0x03U;
    uint8_t matrix_y = row >> 2U;
    uint8_t matrix = (matrix_y << 2U) + matrix_x;
    debug_midi__sysex_p8(D_BOARD, matrix);

    uint8_t local_x = column & 0x03U;
    uint8_t local_y = row & 0x03U;
    uint8_t led = (local_y << 2U) + local_x;
    debug_midi__sysex_p8(D_LED, led);

    // Every LED on the BLM board has 8 associated palette entries.
    // They are assigned as follows (for MB SEQ V4):
    //
    // 0: "black"
    // 1: "green"
    // 2: "red"
    // 3: "yellow"
    // 0: "bright black"    (for future accented note extension)
    // 1: "bright green"    (for future accented note extension)
    // 2: "bright red"      (for future accented note extension)
    // 3: "bright yellow"   (for future accented note extension)
    //
    // So, bits in color_code are mapped to bits in palette entry:
    // Bit 5 (G) -> Bit 0
    // Bit 6 (R) -> Bit 1
    // Bit 4 (ignored, but might be used to carry highest bit of "intensity" value) -> Bit 2
    uint8_t offset = (color_code & 0x20U ? 0x01U : 0x00U)
            | (color_code & 0x40U ? 0x02U : 0x00U)
            | (color_code & 0x10U ? 0x04U : 0x00U);
    uint8_t color = (led << 3U) | offset;
    blm_boards__comm__leds__u128_commands__buffer__put(matrix, led, color);
}
