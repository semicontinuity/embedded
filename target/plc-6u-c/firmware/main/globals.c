#include "util/bitops.h"
#include "cpu/avr/gpio.h"

DEFINE_BITVAR(onewire__thread__alive, SIGNAL_PORT_REG(OUT__INDICATOR1), SIGNAL_PIN(OUT__INDICATOR1));
