// Firmware
#include "kernel.c"
#include CAN_SERVICE_C
#include "comm_service__descriptor_memory.c"
#include "comm_service__handler.c"
#include "main.c"

// BSP
#include CAN_C

#include "../../bsp/water_leak_sensors_scanner.c"
#include "../../bsp/water_valve_controller.c"

// Library
#include "cpu/avr/timer2.c"
#ifndef CAN_EMU
#  include "cpu/avr/int0.c"
#endif
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
