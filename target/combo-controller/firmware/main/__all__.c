//#if defined(CPU_AVR_UTIL_DEBUG)
# include "cpu/avr/util/debug.c"
//#endif

// Firmware
#include "kernel.c"
#include CAN_SERVICE_C
#include "comm_service__descriptor_memory.c"
#include "comm_service.c"

#include "alarm.c"
#include "alarm_timer.c"
#include "alarm__auth.c"

#include "main.c"

//#if defined(SERVICE_CONSOLE)
# include "services/console.c"
# include "util/hex.c"
//#endif


// BSP
#include "seconds_timer.c"
#include CAN_C

#include "../../bsp/motion_sensors_scanner.c"
#include "../../bsp/water_leak_sensors_scanner.c"

// Library
#include "cpu/avr/timer2.c"
#ifndef CAN_EMU
#  include "cpu/avr/int0.c"
#endif
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
