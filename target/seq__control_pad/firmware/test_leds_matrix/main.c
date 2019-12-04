// =============================================================================
// Test LED matrix
// =============================================================================

#include <drivers/io_matrix__out_rows.h>
#include <drivers/io_matrix__out_columns.h>

#include <util/delay.h>

// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_rows__init();
    io_matrix__out_columns__init();
}

void application__start(void) {
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        _delay_ms(500);

        io_matrix__out__column3__set(0);
        io_matrix__out__column0__set(1);
        io_matrix__out_rows__set(0xFF);

        _delay_ms(500);

        io_matrix__out__column0__set(0);
        io_matrix__out__column1__set(1);
        io_matrix__out_rows__set(0xFF);

        _delay_ms(500);

        io_matrix__out__column1__set(0);
        io_matrix__out__column2__set(1);
        io_matrix__out_rows__set(0xFF);

        _delay_ms(500);

        io_matrix__out__column2__set(0);
        io_matrix__out__column3__set(1);
        io_matrix__out_rows__set(0xFF);
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
