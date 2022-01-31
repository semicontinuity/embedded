#include <avr/interrupt.h>
#include <services/gp_buffer.h>


ISR(WDT_vect, ISR_NAKED) {
    gp_buffer__start();
}
