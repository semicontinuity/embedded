#include "util/bitops.h"
#include "cpu/avr/gpio.h"

DEFINE_BITVAR(onewire__bitbang_thread__alive, SIGNAL_PORT_REG(DISPLAY_DIGIT1), SIGNAL_PIN(DISPLAY_SEGMENT_DP));
DEFINE_BITVAR(onewire__thread__alive, SIGNAL_PORT_REG(DISPLAY_DIGIT0), SIGNAL_PIN(DISPLAY_SEGMENT_DP));

#include "main.c"
#include "onewire__t0t2.c"
#include "onewire__bus__inverted_buffer.c"
#include "util/crc8_ow_unrolled.c"
#include "cpu/avr/drivers/display/segment/glyphs__digits__hex.c"
#include "cpu/avr/drivers/display/segment/static2.c"

#include "cpu/avr/util/debug.c"
