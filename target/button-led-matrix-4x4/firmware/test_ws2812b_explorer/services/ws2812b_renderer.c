
#include <stdint.h>
#include <drivers/comm/ws2812b.h>
#include "services/ws2812b_renderer.h"


uint8_t ws2812b_renderer__data[3*16];
volatile bool ws2812b_renderer__refresh;


void ws2812b_renderer__init(void) {
    ws2812b_renderer__refresh = false;
}

void ws2812b_renderer__start(void) {
    ws2812b_renderer__refresh = true;
}

bool ws2812b_renderer__is_runnable(void) {
    return ws2812b_renderer__refresh;
}


void ws2812b_renderer__run(void) {
    ws2812_sendarray_mask(ws2812b_renderer__data, 16*3, _BV(1));
    ws2812b_renderer__refresh = false;
}
