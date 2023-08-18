#include "util/crc16_table2x256.c"

#include "cpu/avr/drivers/comm/modbus/buffer.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__delay_timer.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control__nop.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.c"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_tx.c"
#include "cpu/avr/drivers/comm/modbus/modbus_server.c"
#include "cpu/avr/timer0.c"
#include "cpu/avr/timer2.c"

#include "drivers/in/digital_inputs.c"
#include "drivers/out/digital_outputs.h"
#include "drivers/out/buzzer.h"
#include "drivers/buzzer_timer.c"

#include "drivers/fast_timer.c"
#include "services/slow_timer.c"
#include "services/seconds_timer.c"
#include "services/uptime_counter.c"
#include "services/basic_rtc.c"

#include "services/discrete_inputs.c"
#include "services/coils.c"
#include "services/holding_registers.c"
#include "services/retained_registers.c"

#include "valve_controller__1.c"
#include "contactor_controller.c"
#include "alert_controller.c"
#include "water_leak_sensors_controller.c"
#include "buzzer_control.c"

#include "comm__modbus__callbacks.c"
#include "comm__modbus__coils.c"
#include "comm__modbus__holding_registers.c"
#include "comm__modbus__discrete_inputs.c"

#include "main.c"
