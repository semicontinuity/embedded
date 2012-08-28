// Firmware
#include "main.c"
#include "comm_service.c"
#ifdef CAN_EMU_USART
#  include "usart_service.c"
#else
#include "can_service.c"
#endif


// BSP
#ifndef CAN_EMU_USART
#  include "target/roller-shutter-controller/bsp/can.c"
#endif

#include "target/roller-shutter-controller/bsp/buttons_scanner.c"
#include "target/roller-shutter-controller/bsp/motor_callbacks_nop.c"
#include "target/roller-shutter-controller/bsp/motor_controller.c"
#include "target/roller-shutter-controller/bsp/motor_controller_prescaler.c"
#include "target/roller-shutter-controller/bsp/system_timer.c"

// Library
#ifndef CAN_EMU_USART
#include "cpu/avr/int1.c"
#endif
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
