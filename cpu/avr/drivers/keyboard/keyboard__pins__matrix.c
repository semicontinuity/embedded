// I/O-matrix based keyboard pins
// ---------------------------------------------------------------------------------------------------------------------

#include <cpu/avr/drivers/keyboard/keyboard__pins.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <stdint.h>


// Logical keyboard ports A..D, corresponding to matrix columns 0..3
// ---------------------------------------------------------------------------------------------------------------------

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

uint8_t keyboard__pins__port_a__read(void) {
    return io_matrix__in__column0__state__get();
}

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

uint8_t keyboard__pins__port_b__read(void) {
    return io_matrix__in__column1__state__get();
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

uint8_t keyboard__pins__port_c__read(void) {
    return io_matrix__in__column2__state__get();
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

uint8_t keyboard__pins__port_d__read(void) {
    return io_matrix__in__column3__state__get();
}

#endif


void keyboard__pins__init(void) {
}
