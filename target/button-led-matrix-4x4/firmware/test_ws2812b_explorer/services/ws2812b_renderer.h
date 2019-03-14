#ifndef __SERVICES__WS2812B_RENDERER_H
#define __SERVICES__WS2812B_RENDERER_H

#include <stdbool.h>

extern uint8_t ws2812b_renderer__data[3 * 16];

void ws2812b_renderer__init(void);

void ws2812b_renderer__start(void);

bool ws2812b_renderer__is_runnable(void);

void ws2812b_renderer__run(void);


#endif