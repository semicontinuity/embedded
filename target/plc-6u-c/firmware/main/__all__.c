#include "globals.c"
#include "main.c"

#include "cpu/avr/util/bcd.c"
#include "cpu/avr/drivers/display/segment/glyphs__digits__hex.c"
#include "cpu/avr/drivers/display/segment/static2.c"

#include "buffer.c"
#include "modbus_rtu_driver.c"
#include "modbus_rtu_driver__delay_timer.c"
#include "modbus_rtu_driver__dir_control__rts.c"
#include "modbus_rtu_driver__usart_rx.c"
#include "modbus_rtu_driver__usart_tx.c"
#include "modbus_server.c"
#include "util/crc16_table2x256.c"

#include "services/temperature_reader.c"

#include "drivers/comm/onewire__t0t2.c"
#include "drivers/comm/onewire__bus__noninverting_buffer.c"
#include "util/crc8_ow_unrolled.c"