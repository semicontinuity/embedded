#include <avr/io.h>

#include "util/formatter.c"
#include "util/parser.c"

#include "cpu/avr/drivers/usart0__tx.c"
#include "services/tx_ring_buffer.c"

#include "services/console.c"
#include "services/console_io.c"

#include "main.c"
