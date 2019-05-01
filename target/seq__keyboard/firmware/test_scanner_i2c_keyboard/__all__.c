#include <avr/io.h>

// TX ring buffer first for 256-byte alignment
#include "services/tx_ring_buffer.c"

// LED data
#include "data.c"

// I/O matrix
#include "cpu/avr/timer0.c"
#include "drivers/io_matrix__scanner__thread__timer__timer0.c"
#include "drivers/io_matrix__in.c"
#include "io_matrix__scanner__thread.c"

// Keyboard
#include "cpu/avr/timer2.c"
#include "drivers/keyboard__debounce_timer__timer2.c"
#include "drivers/keyboard__pins__mapping.c"
#include "drivers/keyboard__pins__matrix.c"
#include "cpu/avr/services/keyboard/keyboard.c"

// I2C Comm
#include "I2CSlave.c"
#include "comm__switch.c"

// Entry point
#include "main.c"
