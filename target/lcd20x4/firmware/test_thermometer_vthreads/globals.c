#include "util/bitops.h"
#include "cpu/avr/gpio.h"

DEFINE_BITVAR(onewire__thread__alive, SIGNAL_PORT_REG(OUT__LED3), SIGNAL_PIN(OUT__LED3));
