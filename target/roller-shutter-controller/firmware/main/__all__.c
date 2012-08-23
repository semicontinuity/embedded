// Firmware
#include "main.c"
#include "can_service.c"

// BSP
#include "target/roller-shutter-controller/bsp/can.c"
#include "target/roller-shutter-controller/bsp/buttons_scanner.c"
#include "target/roller-shutter-controller/bsp/motor.c"
#include "target/roller-shutter-controller/bsp/motor_controller.c"
#include "target/roller-shutter-controller/bsp/motor_controller_prescaler.c"
#include "target/roller-shutter-controller/bsp/system_timer.c"

// Library
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"