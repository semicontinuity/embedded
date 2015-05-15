#include "util/bitops.h"
#include "cpu/avr/gpio.h"

DECLARE_BITVAR(onewire__bitbang_thread__alive, SIGNAL_PORT_REG(DISPLAY_DIGIT1), SIGNAL_PIN(DISPLAY_SEGMENT_DP));


#include "main.c"
#include "onewire.c"
#include "onewire__bus__inverted_buffer.c"
#include "util/crc8_ow_unrolled.c"
#include "cpu/avr/drivers/display/segment/glyphs__digits__hex.c"
#include "cpu/avr/drivers/display/segment/static2.c"

#include "cpu/avr/util/debug.c"
