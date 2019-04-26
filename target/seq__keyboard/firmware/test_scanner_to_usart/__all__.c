#include <avr/io.h>

// LED data
#include "data.c"

// I/O matrix
#include "cpu/avr/timer0.c"
#include "drivers/io_matrix__in.c"
#include "drivers/io_matrix__scanner__thread__timer__timer0.c"
#include "io_matrix__scanner__thread.c"

#include "util/formatter.c"

// Entry point
#include "main.c"
