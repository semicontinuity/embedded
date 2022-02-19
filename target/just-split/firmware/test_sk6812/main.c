// =======================================================================0x01*3 + 0======
// SK6812 test - light up 16 RGB LEDs
// =============================================================================

#include <util/delay.h>
//#include "leds.h"


void application__init(void) {
  leds__init();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_ms(500);

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        leds__data[0x00*3 + 0]=0xFF; leds__data[0x00*3 + 1]=0x00; leds__data[0x00*3 + 2]=0x00;
        leds__data[0x01*3 + 0]=0x00; leds__data[0x01*3 + 1]=0xFF; leds__data[0x01*3 + 2]=0x00;
        leds__data[0x02*3 + 0]=0x00; leds__data[0x02*3 + 1]=0x00; leds__data[0x02*3 + 2]=0xFF;
        leds__data[0x03*3 + 0]=0x40; leds__data[0x03*3 + 1]=0x40; leds__data[0x03*3 + 2]=0x40;
        leds__data[0x04*3 + 0]=0x20; leds__data[0x04*3 + 1]=0x00; leds__data[0x04*3 + 2]=0x00;
        leds__data[0x05*3 + 0]=0x00; leds__data[0x05*3 + 1]=0x20; leds__data[0x05*3 + 2]=0x00;
        leds__data[0x06*3 + 0]=0x00; leds__data[0x06*3 + 1]=0x00; leds__data[0x06*3 + 2]=0x20;
        leds__data[0x07*3 + 0]=0x30; leds__data[0x07*3 + 1]=0x30; leds__data[0x07*3 + 2]=0x30;

        leds__data[0x08*3 + 0]=0x40; leds__data[0x08*3 + 1]=0x00; leds__data[0x08*3 + 2]=0x00;
        leds__data[0x09*3 + 0]=0x00; leds__data[0x09*3 + 1]=0x40; leds__data[0x09*3 + 2]=0x00;
        leds__data[0x0a*3 + 0]=0x00; leds__data[0x0a*3 + 1]=0x00; leds__data[0x0a*3 + 2]=0x40;
        leds__data[0x0b*3 + 0]=0x20; leds__data[0x0b*3 + 1]=0x20; leds__data[0x0b*3 + 2]=0x20;
        leds__data[0x0c*3 + 0]=0x60; leds__data[0x0c*3 + 1]=0x00; leds__data[0x0c*3 + 2]=0x00;
        leds__data[0x0d*3 + 0]=0x00; leds__data[0x0d*3 + 1]=0x60; leds__data[0x0d*3 + 2]=0x00;
        leds__data[0x0e*3 + 0]=0x00; leds__data[0x0e*3 + 1]=0x00; leds__data[0x0e*3 + 2]=0x60;
        leds__data[0x0f*3 + 0]=0x10; leds__data[0x0f*3 + 1]=0x10; leds__data[0x0f*3 + 2]=0x10;

        leds__data[0x10*3 + 0]=0x00; leds__data[0x10*3 + 1]=0x00; leds__data[0x10*3 + 2]=0x60;
        leds__data[0x11*3 + 0]=0x10; leds__data[0x11*3 + 1]=0x10; leds__data[0x11*3 + 2]=0x10;
        leds__data[0x12*3 + 0]=0xFF; leds__data[0x12*3 + 1]=0xFF; leds__data[0x12*3 + 2]=0xFF;

        leds__refresh__set(1);
        leds__run();
        _delay_ms(500);

        leds__data[0x00*3 + 0]=0x01; leds__data[0x00*3 + 1]=0x01; leds__data[0x00*3 + 2]=0x00;
        leds__data[0x01*3 + 0]=0x00; leds__data[0x01*3 + 1]=0x01; leds__data[0x01*3 + 2]=0x01;
        leds__data[0x02*3 + 0]=0x01; leds__data[0x02*3 + 1]=0x00; leds__data[0x02*3 + 2]=0x01;
        leds__data[0x03*3 + 0]=0x01; leds__data[0x03*3 + 1]=0x01; leds__data[0x03*3 + 2]=0x01;
        leds__data[0x04*3 + 0]=0x02; leds__data[0x04*3 + 1]=0x02; leds__data[0x04*3 + 2]=0x00;
        leds__data[0x05*3 + 0]=0x00; leds__data[0x05*3 + 1]=0x02; leds__data[0x05*3 + 2]=0x02;
        leds__data[0x06*3 + 0]=0x02; leds__data[0x06*3 + 1]=0x00; leds__data[0x06*3 + 2]=0x02;
        leds__data[0x07*3 + 0]=0x02; leds__data[0x07*3 + 1]=0x02; leds__data[0x07*3 + 2]=0x02;

        leds__data[0x08*3 + 0]=0x04; leds__data[0x08*3 + 1]=0x04; leds__data[0x08*3 + 2]=0x00;
        leds__data[0x09*3 + 0]=0x00; leds__data[0x09*3 + 1]=0x04; leds__data[0x09*3 + 2]=0x04;
        leds__data[0x0a*3 + 0]=0x04; leds__data[0x0a*3 + 1]=0x00; leds__data[0x0a*3 + 2]=0x04;
        leds__data[0x0b*3 + 0]=0x04; leds__data[0x0b*3 + 1]=0x04; leds__data[0x0b*3 + 2]=0x04;
        leds__data[0x0c*3 + 0]=0x02; leds__data[0x0c*3 + 1]=0x00; leds__data[0x0c*3 + 2]=0x00;
        leds__data[0x0d*3 + 0]=0x00; leds__data[0x0d*3 + 1]=0x02; leds__data[0x0d*3 + 2]=0x00;
        leds__data[0x0e*3 + 0]=0x00; leds__data[0x0e*3 + 1]=0x00; leds__data[0x0e*3 + 2]=0x02;
        leds__data[0x0f*3 + 0]=0x02; leds__data[0x0f*3 + 1]=0x02; leds__data[0x0f*3 + 2]=0x02;

        leds__data[0x10*3 + 0]=0x00; leds__data[0x10*3 + 1]=0x00; leds__data[0x10*3 + 2]=0x60;
        leds__data[0x11*3 + 0]=0x10; leds__data[0x11*3 + 1]=0x10; leds__data[0x11*3 + 2]=0x10;
        leds__data[0x12*3 + 0]=0xFF; leds__data[0x12*3 + 1]=0xFF; leds__data[0x12*3 + 2]=0x00;

        leds__refresh__set(1);
        leds__run();
        _delay_ms(500);

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
