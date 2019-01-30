#include "cpu/avr/twi.h"
#include "drivers/i2c_slave.h"

bool i2c_slave__thread__is_runnable(void) {
    return true;
}