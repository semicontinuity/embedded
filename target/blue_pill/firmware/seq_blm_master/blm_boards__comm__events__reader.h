// Reads button and encoder events from BLM boards.
// -----------------------------------------------------------------------------
#define LC_INCLUDE "lc-addrlabels.h"
#include "blm_boards__comm__events__reader__callbacks.h"
#include <Arduino.h>
#include <pt.h>


uint8_t blm_boards__comm_events__reader__read(uint8_t board);


static struct pt blm_boards__comm_events__reader__thread;
static uint8_t blm_boards__comm_events__reader__current = 0;


void blm_boards__comm_events__reader__init() {
    PT_INIT(&blm_boards__comm_events__reader__thread);
}


int blm_boards__comm_events__reader__run() {
    struct pt *pt = &blm_boards__comm_events__reader__thread;
    PT_BEGIN(pt);

    while (true) {
        uint8_t current = blm_boards__comm_events__reader__current;
        uint8_t event = blm_boards__comm_events__reader__read(current);
        ++current;
        if (current >= BLM_SCALAR_NUM_BOARDS) current = 0;
        blm_boards__comm_events__reader__current = current;

        if (event) {

        }

        PT_YIELD(pt);
    }

    PT_END(pt);
}
