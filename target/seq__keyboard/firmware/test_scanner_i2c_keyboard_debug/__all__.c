#include <avr/io.h>

// LED data
#include "data.c"

// I/O matrix
#include "cpu/avr/timer0.c"
#include "cpu/avr/drivers/io_matrix/io_matrix__in.c"
#include "drivers/io_matrix__scanner__thread__timer__timer0.c"
#include "io_matrix__scanner__thread.c"

// I2C Comm
#include "I2CSlave.c"
#include "comm__switch.c"

// Entry point
#include "main.c"
