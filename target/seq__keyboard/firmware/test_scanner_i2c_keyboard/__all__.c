#include <avr/io.h>

// TX ring buffer first for 256-byte alignment
#include "services/tx_ring_buffer.c"

// Keyboard
#include "cpu/avr/timer2.c"
#include "drivers/keyboard__debounce_timer__timer2.c"
#include "drivers/keyboard.c"
#include "drivers/keyboard__pins__mapping.c"

// LED data
#include "data.c"

// Scanner
#include "drivers/io_matrix__in.c"
#include "drivers/scanner__thread__timer.c"
#include "cpu/avr/timer0.c"
#include "scanner.c"

// I2C Comm
#include "I2CSlave.c"
#include "comm__switch.c"

// Entry point
#include "main.c"
