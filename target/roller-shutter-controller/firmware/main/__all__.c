// Firmware
#include "main.c"
#include "kernel.c"
#include CAN_SERVICE_C
#include "comm_service__descriptor_memory.c"
#include "comm_service__handler.c"

// BSP
#include CAN_C

#include "target/roller-shutter-controller/bsp/buttons_scanner.c"
#include "target/roller-shutter-controller/bsp/motor_callbacks_nop.c"
#include "target/roller-shutter-controller/bsp/motor_controller.c"
#include "target/roller-shutter-controller/bsp/motor_controller_prescaler.c"

// Library
#include "cpu/avr/timer2.c"
#ifndef CAN_EMU
#  include "cpu/avr/int0.c"
#endif
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"

#include "cpu/avr/util/debug.c"