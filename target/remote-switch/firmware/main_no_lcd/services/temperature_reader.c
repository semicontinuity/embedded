//#include "drivers/out/led1.h"
//#include "drivers/out/led2.h"

#include "services/temperature_reader.h"

#include "drivers/comm/onewire.h"
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/timer0.h"
//#include <util/delay.h>


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

/** Instruction pointer */
#ifdef TEMPERATURE_READER__THREAD__IP__REG
register void* temperature_reader__thread__ip asm(QUOTE(TEMPERATURE_READER__THREAD__IP__REG));
#else
volatile void *temperature_reader__thread__ip;
#endif

volatile uint8_t onewire__thread__delay_counter;


void temperature_reader__thread__start(void) {
    VT_INIT(temperature_reader__thread, temperature_reader__thread__ip);
    timer0__conf__set(TIMER0_CONF_PRESCALER_1024|TIMER0_CONF_WGM_NORMAL);
}

bool temperature_reader__thread__is_runnable(void) {
    return timer0__overflow__interrupt__pending__get();
}

void temperature_reader__thread__run(void) {
    VT_BEGIN(temperature_reader__thread, temperature_reader__thread__ip);
    timer0__overflow__interrupt__pending__clear();
    for (;;) {
//        led1__set(1);
//        led2__set(1);

        onewire__setup_transaction((uint8_t) sizeof(command_convert), 0, command_convert, 0);
        onewire__transaction();
        do {
            VT_YIELD_WITH_MARK(temperature_reader__thread, temperature_reader__thread__ip, COMMAND_CONVERT);
            onewire__thread__run();
        }
        while (onewire__thread__is_alive());

//        led1__set(1);
//        led2__set(0);

        onewire__thread__delay_counter = 46;
        timer0__conf__set(TIMER0_CONF_PRESCALER_1024|TIMER0_CONF_WGM_NORMAL);
        for (;;) {            
            VT_YIELD_WITH_MARK(temperature_reader__thread, temperature_reader__thread__ip, SLEEP);
            timer0__overflow__interrupt__pending__clear();
            if (--onewire__thread__delay_counter == 0) break;
        }

//        led1__set(0);
//        led2__set(1);

        onewire__setup_transaction(sizeof(command), sizeof(response), command, response);
        onewire__transaction();
        do {
            VT_YIELD_WITH_MARK(temperature_reader__thread, temperature_reader__thread__ip, COMMAND_READ);
            onewire__thread__run();
        }
        while (onewire__thread__is_alive());

//        led1__set(0);
//        led2__set(0);

        temperature_reader__reading = (response[0] | (response[1] << 8)) << 4;
        temperature_reader__reading__on_changed();

//        _delay_ms(1);
    }
    VT_UNREACHEABLE_END(temperature_reader__thread);
}

