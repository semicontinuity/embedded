// =============================================================================
// Test XMEGA int. oscillator and GPIO.
// =============================================================================

#include <avr/io.h>
#include <avr/interrupt.h>

// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    OSC_CTRL = (1<<OSC_RC32MEN_bp);               // enable internal 32MHz generator
    while (!(OSC_STATUS & (1<<OSC_RC32MRDY_bp))); // wait for internal 32MHz generator

    CCP = 0xD8;                         // enable write to CLK_CTRL
    CLK_CTRL = (1<<CLK_SCLKSEL0_bp);    // select internal 32MHz oscillator


    PORTC_DIR = (1<<PIN4_bp); // PC4 is output
    PORTC_OUT = (1<<PIN4_bp); // PC4 = 1

    for(;;);

    return 0;
}
