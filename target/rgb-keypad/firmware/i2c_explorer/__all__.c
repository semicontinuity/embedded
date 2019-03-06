#include <avr/io.h>

#include "drivers/i2c_master.c"

#include "services/console.c"
#include "util/formatter.c"
#include "util/parser.c"

#include "cpu/avr/drivers/usart0__tx.c"
#include "services/tx_ring_buffer.c"

#include "main.c"
