#include "int1.h"
#include <avr/interrupt.h>

ISR(INT1_vect) {
    int1__run();
}
