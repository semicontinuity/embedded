#include "device.h"
#include <avr/interrupt.h>

#include "can_service.h"
#include "cpu/avr/asm.h"

#define CAN_CONTROLLER_INTERRUPT ISR(INT1_vect, ISR_NAKED)


static void can_service__handle_rx(void) {

}


CAN_CONTROLLER_INTERRUPT {
    // interrupt flag for INT0 cleared automatically
    // The only source of interrupt is from RX buffer 0
    can_service__handle_rx();

    // Clear all interrupts
    MCP251X_SPI_COMM(mcp251x_write_byte(MCP251X_REGISTER_CANINTF, 0));

    RETI();
}
