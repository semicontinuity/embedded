// LED data
#include "data.c"

// I/O matrix
#include "cpu/avr/timer1.c"
#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c"
#include "cpu/avr/drivers/io_matrix/io_matrix__in.c"
#include "io_matrix__scanner__thread.c"

// I2C Comm
#include "twi_slave__handler.c"
#include "comm_events_simple.c"
#include "comm_leds.c"

// Tracing
#include "services/tracer__nop.c"

// Entry point
#include "main.c"
