// Kernel
// -----------------------------------------------------------------------------
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
#include "drivers/net/can/mcp251x/rx.c"
#include "drivers/net/can/mcp251x/tx.c"
#include "drivers/net/can/mcp251x/int_handler.c"
#include "cpu/avr/int0.c"
#include "kernel.c"

// Application
// -----------------------------------------------------------------------------

//#if defined(CPU_AVR_UTIL_DEBUG)
# include "cpu/avr/util/debug.c"
//#endif

//#if defined(SERVICE_CONSOLE)
# include "services/console.c"
# include "util/hex.c"
//#endif


// BSP

#include "services/seconds_timer.c"
#include "motion_sensors_scanner.c"
#include "water_leak_sensors_scanner.c"

// Library
#include "cpu/avr/timer2.c"


// Firmware
#include "descriptor.c"
#include "comm_service.c"

#include "drivers/out/amplifier_relay.c"
#include "drivers/out/water_valve.c"

#include "services/alarm.c"
#include "services/alarm__timer.c"
#include "services/alarm__auth.c"
#include "services/water_leak_handler__timer.c"

#include "endpoints/alarm__state.c"
#include "endpoints/siren1.c"
#include "endpoints/siren2.c"
#include "endpoints/emergency__water_actuators__0.c"
#include "endpoints/emergency__water_sensors__0.c"
#include "endpoints/presense__motion_sensors__0.c"
#include "endpoints/media__amplifier__0.c"

#include "main.c"
