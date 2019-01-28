// =============================================================================
// Water counter driver.
// =============================================================================


#include <avr/io.h>
#include <drivers/water_counter.h>


void water_counter__init(void) {
    ACSR = 0;
}


void water_counter__start(void) {
}
