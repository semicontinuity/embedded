#include <avr/io.h>

#include "cpu/avr/timer0.c"
#include "drivers/keyboard__debounce_timer.c"
#include "services/tx_ring_buffer.c"
#include "keyboard.c"

#include "I2CSlave.c"
#include "comm__switch.c"
#include "drivers/comm/ws2812b.c"

#include "main.c"
