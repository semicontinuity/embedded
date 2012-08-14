#include "device.h"
#include <avr/interrupt.h>
#include "cpu/avr/asm.h"

#define CAN_CONTROLLER_INTERRUPT ISR(INT1_vect, ISR_NAKED)


CAN_CONTROLLER_INTERRUPT {
    RETI();
}
