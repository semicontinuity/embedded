// Scans LED state data structures
// and produces on BLM board LED update commands.
// May generate up to 1 LED update command on every invocation
// of blm_boards_leds__state_scanner__run().
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdbool.h>
#include "blm_boards_leds__state.h"
#include "blm_boards_leds__state_scanner_callbacks.h"

uint8_t led_state = 0;
uint8_t led_state2 = 0;

void debug_scanner8(uint8_t param, uint8_t v) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((v >> 4) & 0x0F);
    Serial2.write(v & 0x0F);
    Serial2.write(0xf7);
}


void debug_scanner16(uint8_t param, uint16_t v) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((v >> 12) & 0x0F);
    Serial2.write((v >> 8) & 0x0F);
    Serial2.write((v >> 4) & 0x0F);
    Serial2.write(v & 0x0F);
    Serial2.write(0xf7);
}

void debug_scanner32(uint8_t param, uint32_t v) {
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


/** @return true if the board became synchronized (clean), false otherwise */
static bool blm_boards_leds__state_scanner__scan(unsigned int board) {
    digitalWrite(PA1, 1);
    debug_scanner8(1, board);

    uint32_t current = blm_boards_leds__state__current[board];
    debug_scanner32(0x10, current);
    uint32_t requested = blm_boards_leds__state__requested[board];
    debug_scanner32(0x11, requested);

    uint32_t raw_diff = current ^ requested;
    debug_scanner32(0x14, raw_diff);
    uint16_t green_diff = raw_diff & 0xFFFFU;
    debug_scanner16(0x15, green_diff);
    uint16_t red_diff = (raw_diff >> 16U) & 0xFFFFU;
    debug_scanner16(0x16, red_diff);
    uint16_t diff = green_diff | red_diff;
    debug_scanner16(0x17, red_diff);
    if (diff) {
        digitalWrite(PA1, 1);
    }
    int led = __builtin_ffs(diff) - 1;
    debug_scanner8(0x20, led);
    if (led >= 0) { // must be always true if there are no bugs
//        digitalWrite(PA1, led_state = ~led_state);
        digitalWrite(PA5, 1);

        uint32_t green_mask = 1U << (uint32_t)led;
        uint32_t green = requested & green_mask;
        if (green) {
            current |= green_mask;
            green = 0xFF;
        } else {
            current &= ~green_mask;
        }

        uint32_t red_mask = green_mask << 16U;
        uint32_t red = requested & red_mask;
        if (red) {
            current |= red_mask;
            red = 0xFF;
        } else {
            current &= ~red_mask;
        }

        blm_boards_leds__state__current[board] = current;
        debug_scanner32(0x10, blm_boards_leds__state__current[board]);

        blm_boards_leds__state_scanner__scan__update_one(board, led, red, green, 0);
    } else {
//        digitalWrite(PA5, 0);
    }
    return current == requested;
}


void blm_boards_leds__state_scanner__run() {
//    digitalWrite(PA1, blm_boards_leds__state__dirty);

    int board = __builtin_ffs(blm_boards_leds__state__dirty) - 1;
    if (board >= 0) {
//        digitalWrite(PA5, led_state2 = ~led_state2);
        if (blm_boards_leds__state_scanner__scan(board)) {
            blm_boards_leds__state__dirty &= ~(1U << (uint32_t) board);
        }
    } else {
//        digitalWrite(PA1, 0);
    }
    // as optimisation, if all boards are clean, "suspend" the thread, and wake it up when LED updates are received.
    // (on the other hand, this check is quite fast anyway)
}
