#include <avr/io.h>

#include "util/formatter.c"
#include "util/parser.c"

#include "drivers/i2c_master.c"
#include "cpu/avr/drivers/usart0__tx.c"
#include "services/tx_ring_buffer.c"

#include "services/console.c"
#include "services/console_i2c.c"

#include "main.c"
