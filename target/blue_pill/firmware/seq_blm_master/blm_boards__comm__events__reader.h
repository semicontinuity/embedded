// Reads button and encoder events from BLM boards.
// -----------------------------------------------------------------------------

#define LC_INCLUDE "lc-addrlabels.h"
#include "blm_boards__comm__events__handler.h"
#include <Arduino.h>
#include <pt.h>


uint8_t blm_boards__comm_events__reader__read(uint8_t board);


static struct pt blm_boards__comm_events__reader__thread;
static uint8_t blm_boards__comm_events__reader__board = 0;


void blm_boards__comm_events__reader__init() {
    PT_INIT(&blm_boards__comm_events__reader__thread);
}


int blm_boards__comm_events__reader__run() {
    struct pt *pt = &blm_boards__comm_events__reader__thread;
    PT_BEGIN(pt);

    while (true) {
        uint8_t board = blm_boards__comm_events__reader__board;
        uint8_t event = blm_boards__comm_events__reader__read(board);
        ++board;
        if (board >= BLM_SCALAR_NUM_BOARDS) board = 0;
        blm_boards__comm_events__reader__board = board;

        if (event) {
            bool is_pressed = event >= 'a';
            uint8_t button = (event | 0x20) - 'a';
            blm_boards__comm_events__handler__on_button_event(board, button, is_pressed);
        }

        PT_YIELD(pt);
    }

    PT_END(pt);
}