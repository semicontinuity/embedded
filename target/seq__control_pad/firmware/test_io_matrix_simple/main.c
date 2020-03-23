// =============================================================================
// Test I/O matrix
// =============================================================================

//#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
//#include <drivers/io_matrix__in.h>
#include <drivers/io_matrix__out_rows.h>
#include <drivers/io_matrix__out_columns.h>

#include <util/delay.h>

// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_rows__init();
    io_matrix__out_columns__init();
    io_matrix__in__init();
}

void application__start(void) {
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    io_matrix__out__column0__set(1);
    io_matrix__out__column1__set(1);
    io_matrix__out__column2__set(1);
    io_matrix__out__column3__set(1);

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        io_matrix__in__column0__state__update();
        uint8_t state = io_matrix__in__column0__state__get();
        uint8_t output = 0x00;

        if (!(state & (1U << IO_MATRIX__IN__ROW0__PIN))) {
            output |= (1U << IO_MATRIX__OUT__ROW0__PIN);
        }
        if (!(state & (1U << IO_MATRIX__IN__ROW1__PIN))) {
            output |= (1U << IO_MATRIX__OUT__ROW1__PIN);
        }
        if (!(state & (1U << IO_MATRIX__IN__ROW2__PIN))) {
            output |= (1U << IO_MATRIX__OUT__ROW2__PIN);
        }
        if (!(state & (1U << IO_MATRIX__IN__ROW3__PIN))) {
            output |= (1U << IO_MATRIX__OUT__ROW3__PIN);
        }
        if (!(state & (1U << IO_MATRIX__IN__ROW4__PIN))) {
            output |= (1U << IO_MATRIX__OUT__ROW4__PIN);
        }

        io_matrix__out_rows__set(output);
    }

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}
