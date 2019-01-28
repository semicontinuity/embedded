// Library
#include "cpu/avr/spi_polled.c"
#include "cpu/avr/timer2.c"

// Kernel
// -----------------------------------------------------------------------------
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
#include "drivers/net/can/mcp251x/rx.c"
#include "drivers/net/can/mcp251x/tx.c"
#include "drivers/net/can/mcp251x/int_handler.c"
#include "cpu/avr/int0.c"
#include "kernel.c"

// Firmware
#include "module_descriptor.c"
#include "main.c"
#include "comm_service.c"
#include "endpoints/comm__bits__0.c"
#include "endpoints/mechatronics__linear_actuator_current_value__0.c"
#include "endpoints/mechatronics__linear_actuator_target_value__0.c"
#include "endpoints/mechatronics__linear_actuator_mode__0.c"
#include "endpoints/mechatronics__linear_actuator_precision__0.c"

// BSP
#include "target/roller-shutter-controller/bsp/buttons_scanner.c"
#include "target/roller-shutter-controller/bsp/motor_callbacks_nop.c"
#include "target/roller-shutter-controller/bsp/motor_controller.c"
#include "target/roller-shutter-controller/bsp/motor_controller_prescaler.c"
