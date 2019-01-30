#include "cpu/avr/twi.h"
#include "drivers/twi_slave.h"

bool twi_slave__thread__is_runnable(void) {
    return twi__is_software_action_required();
}


void twi_slave__thread__run(void) {
    twi__continue(true, true);
}
