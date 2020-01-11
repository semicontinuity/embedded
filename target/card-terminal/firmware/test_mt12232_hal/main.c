#include "cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h"

uint8_t buffer[122];

int main(int argc, char **argv) {
    for (uint8_t i = 0; i < 122; i++) {
        buffer[i] = 0xAA;
    }

    mt12232_hal__init();
    mt12232_hal__send_strip(buffer, 0, 0, 61);
    mt12232_hal__send_strip(buffer, 1, 61, 122);
    mt12232_hal__send_strip(buffer, 2, 0, 122);
    mt12232_hal__send_strip(buffer, 3, 30, 92);

    while(1);
    return 0;
}
