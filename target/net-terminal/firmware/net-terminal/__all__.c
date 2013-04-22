// Firmware
#include "kernel.c"
#include CAN_SERVICE_C
#include "comm_service__descriptor_memory.c"
#include "comm_service.c"

#include "alarm_client__auth.c"

#include "main.c"

//#include "console_service.c"
//#include "parse.c"
//# include "cpu/avr/util/debug.c"


// BSP
#include CAN_C


// Library
#include "cpu/avr/timer2.c"
#ifndef CAN_EMU
#  include "cpu/avr/int1.c"
#endif
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"

#include "cpu/avr/drivers/display/mt12864/terminal.c"
#include "cpu/avr/drivers/display/mt12864/text-output.c"
#include "cpu/avr/drivers/display/mt12864/bitblt.c"
#include "cpu/avr/drivers/display/mt12864/driver.c"
#include "util/font/Font_6x8.c"
