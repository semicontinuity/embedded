#include <avr/io.h>

#include "services/tx_ring_buffer.c"

#include "cpu/avr/timer2.c"
#include "drivers/keyboard__debounce_timer__timer2.c"
#include "keyboard.c"
#include "keyboard__pins__logical.c"
#include "keyboard__pins__mapping.c"

#include "data.c"

#include "drivers/scanner__thread__timer.c"
#include "cpu/avr/timer0.c"
#include "scanner__thread.c"

#include "I2CSlave.c"
#include "comm__switch.c"

#include "main.c"
