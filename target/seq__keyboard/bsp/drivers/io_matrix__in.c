#include "drivers/io_matrix__in.h"
#include <stdint.h>
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


// Column states
// ---------------------------------------------------------------------------------------------------------------------

#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
register volatile uint8_t io_matrix__in__column0__state asm(QUOTE(IO_MATRIX__IN__COLUMN0__STATE__REG));
#else
volatile uint8_t io_matrix__in__column0__state;
#endif


void io_matrix__in__column0__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
    __IN(io_matrix__in__column0__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column0__state = IN(IO_MATRIX__IN);
#endif
}

uint8_t io_matrix__in__column0__state__get(void) {
    return io_matrix__in__column0__state;
}



#ifdef IO_MATRIX__IN__COLUMN1__STATE__REG
register volatile uint8_t io_matrix__in__column1__state asm(QUOTE(IO_MATRIX__IN__COLUMN1__STATE__REG));
#else
volatile uint8_t io_matrix__in__column1__state;
#endif


void io_matrix__in__column1__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN1__STATE__REG
    __IN(io_matrix__in__column1__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column1__state = IN(IO_MATRIX__IN);
#endif
}

uint8_t io_matrix__in__column1__state__get(void) {
    return io_matrix__in__column1__state;
}



#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
register volatile uint8_t io_matrix__in__column2__state asm(QUOTE(IO_MATRIX__IN__COLUMN2__STATE__REG));
#else
volatile uint8_t io_matrix__in__column2__state;
#endif


void io_matrix__in__column2__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
    __IN(io_matrix__in__column2__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column2__state = IN(IO_MATRIX__IN);
#endif
}

uint8_t io_matrix__in__column2__state__get(void) {
    return io_matrix__in__column2__state;
}



#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
register volatile uint8_t io_matrix__in__column3__state asm(QUOTE(IO_MATRIX__IN__COLUMN3__STATE__REG));
#else
volatile uint8_t io_matrix__in__column3__state;
#endif


void io_matrix__in__column3__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
    __IN(io_matrix__in__column3__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column3__state = IN(IO_MATRIX__IN);
#endif
}

uint8_t io_matrix__in__column3__state__get(void) {
    return io_matrix__in__column3__state;
}



inline void io_matrix__in__init(void) {
    USE_AS_INPUT(IO_MATRIX__IN__BUTTONS_ENCODERS_A);
    ENABLE_PULLUP(IO_MATRIX__IN__BUTTONS_ENCODERS_A);
    USE_AS_INPUT(IO_MATRIX__IN__BUTTONS_ENCODERS_B);
    ENABLE_PULLUP(IO_MATRIX__IN__BUTTONS_ENCODERS_B);

    USE_AS_INPUT(IO_MATRIX__IN__BUTTONS_ROW0);
    ENABLE_PULLUP(IO_MATRIX__IN__BUTTONS_ROW0);
    USE_AS_INPUT(IO_MATRIX__IN__BUTTONS_ROW1);
    ENABLE_PULLUP(IO_MATRIX__IN__BUTTONS_ROW1);
    USE_AS_INPUT(IO_MATRIX__IN__BUTTONS_ROW2);
    ENABLE_PULLUP(IO_MATRIX__IN__BUTTONS_ROW2);
    USE_AS_INPUT(IO_MATRIX__IN__BUTTONS_ROW3);
    ENABLE_PULLUP(IO_MATRIX__IN__BUTTONS_ROW3);

    io_matrix__in__column0__state = 0xFF;
    io_matrix__in__column1__state = 0xFF;
    io_matrix__in__column2__state = 0xFF;
    io_matrix__in__column3__state = 0xFF;
}
