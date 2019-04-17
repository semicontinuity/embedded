#include <avr/io.h>

#include "util/formatter.c"
#include "util/parser.c"

#include "cpu/avr/drivers/usart0__tx.c"
#include "services/tx_ring_buffer.c"

#include "comm__switch.c"
#include "I2CSlave.c"

#include "services/console.c"
#include "services/console__in__polled.c"
#include "services/console__out__buffered.c"
#include "services/console_i2c_slave.c"

#include "main.c"
