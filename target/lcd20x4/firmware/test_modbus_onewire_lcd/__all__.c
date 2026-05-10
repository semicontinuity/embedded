#include "globals.c"
#include "main.c"

#include "cpu/avr/util/bcd.c"

#include "cpu/avr/drivers/display/hd44780/hd44780.c"

#include "cpu/avr/drivers/comm/modbus/buffer.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__delay_timer.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control__nop.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_tx.c"
#include "cpu/avr/drivers/comm/modbus/modbus_server.c"
#include "util/crc16_table2x256.c"

#include "services/temperature_reader.c"

#include "drivers/comm/onewire__t0t2.c"
#include "drivers/comm/onewire__bus__direct.c"
#include "util/crc8_ow_unrolled.c"
