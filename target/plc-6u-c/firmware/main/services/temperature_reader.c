#include "services/temperature_reader.h"

#include "drivers/comm/onewire.h"
#include "cpu/avr/util/vthreads.h"
#include <util/delay.h>


#define OW_SKIP_ROM	        0xCC
#define DS18X20_CONVERT_T   0x44
#define DS18X20_READ	    0xBE
#define DS18X20_SP_SIZE     9

uint16_t temperature_reader__reading;

uint8_t command_convert[] = {OW_SKIP_ROM, DS18X20_CONVERT_T};
uint8_t command[] = {OW_SKIP_ROM, DS18X20_READ};
uint8_t response[DS18X20_SP_SIZE];

//#include <stdio.h>


//int usart_putchar(char c, FILE *stream) {
//    usart0__out__write(c);
//    return 0;
//}

//bool temperature_reader__thread__is_runnable(void) {
//
//}

void temperature_reader__thread__run(void) {
    onewire__command((uint8_t)sizeof(command_convert), 0, command_convert, 0);
    do {
        if (onewire__thread__is_runnable())
            onewire__thread__run();
//        else
//            sleep_cpu();
    }
    while (onewire__thread__is_alive());

    _delay_ms(750);

    onewire__command(sizeof(command), sizeof(response), command, response);
    do {
        if (onewire__thread__is_runnable())
            onewire__thread__run();
//        else
//            sleep_cpu();
    }
    while (onewire__thread__is_alive());

    temperature_reader__reading = (response[0] | (response[1] << 8)) << 4;
    temperature_reader__reading__on_changed();

    _delay_ms(1);
}

