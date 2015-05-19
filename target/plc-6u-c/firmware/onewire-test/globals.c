#include "util/bitops.h"
#include "cpu/avr/gpio.h"

DEFINE_BITVAR(onewire__thread__alive, SIGNAL_PORT_REG(DISPLAY_DIGIT0), SIGNAL_PIN(DISPLAY_SEGMENT_DP));
