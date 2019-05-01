#include <avr/io.h>

#include "services/tx_ring_buffer.c"

#include "cpu/avr/timer0.c"
#include "drivers/keyboard__debounce_timer__timer0.c"
#include "drivers/keyboard__pins__physical.c"
#include "drivers/keyboard__pins__mapping.c"
#include "cpu/avr/services/keyboard/keyboard.c"

#include "I2CSlave.c"
#include "comm__switch.c"

#include "drivers/comm/ws2812b.c"

#include "main.c"
