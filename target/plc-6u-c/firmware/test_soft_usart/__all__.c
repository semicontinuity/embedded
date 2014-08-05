#include <avr/io.h>
#include "util/bitops.h"
DECLARE_BITVAR(soft_usart__rx__in_data_bits, SOFT_USART__RX__IN_DATA_BITS__HOST, SOFT_USART__RX__IN_DATA_BITS__BIT);
DECLARE_BITVAR(soft_usart__rx__in_stop_bit, SOFT_USART__RX__IN_STOP_BIT__HOST, SOFT_USART__RX__IN_STOP_BIT__BIT);

#include "main.c"

#include "cpu/avr/drivers/display/segment/glyphs__digits__hex.c"
#include "cpu/avr/drivers/display/segment/static2.c"

#include "cpu/avr/drivers/comm/soft_usart__rx.c"
#include "cpu/avr/drivers/comm/soft_usart__tx.c"
#include "cpu/avr/timer2.c"
#include "cpu/avr/int0.c"
