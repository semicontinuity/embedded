// =============================================================================
// Main program.
// =============================================================================
#include <avr/io.h>
#include "motor.h"

// =============================================================================
// Entry point
// =============================================================================
int main(void) {
    motor__up__init();
    motor__down__init();

//    motor__down__on();

//    if (MCUCR == 0x00) {
//        motor__up__on();
//    }
/*
    MCUCR = 0x01;
    MCUCR = 0x02;

    if (MCUCR == 0x02) {
        motor__down__on();
    }
*/


    if (MCUCR == 0x02) {
        // Indicate STOP mode
        motor__up__on();
    }
    else {
        //motor__up__on();

        // Request STOP mode
        MCUCR = 0x01;
        MCUCR = 0x02;
        asm("rjmp __vectors");
    }

    return 0;
}
