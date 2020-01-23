#ifndef __BLM_BOARDS_LEDS__STATE
#define __BLM_BOARDS_LEDS__STATE

#include <stdint.h>

uint32_t blm_boards_leds__state__current[16];
uint32_t blm_boards_leds__state__requested[16];
uint16_t blm_boards_leds__state__dirty;

#endif
