#include "drivers/out/led1.h"
#include "drivers/out/led2.h"

#include "services/temperature_reader.h"

#include "drivers/comm/onewire.h"
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/timer0.h"


#define OW_MATCH_ROM	    0x55
#define OW_SKIP_ROM	        0xCC
#define DS18X20_CONVERT_T   0x44
#define DS18X20_READ	    0xBE
#define DS18X20_SP_SIZE     9

uint16_t temperature_reader__readings[DS18X20_SENSOR_COUNT];

#define DS18X20_COMMAND_SIZE 10
#define DS18X20_CONVERT_T_WITH_ROM(rom) OW_MATCH_ROM, rom, DS18X20_CONVERT_T
#define DS18X20_READ_WITH_ROM(rom)      OW_MATCH_ROM, rom, DS18X20_READ

uint8_t commands[] = {
#if defined(DS18X20_1)
    DS18X20_CONVERT_T_WITH_ROM(DS18X20_1),
    DS18X20_READ_WITH_ROM(DS18X20_1),
#endif
#if defined(DS18X20_2)
    DS18X20_CONVERT_T_WITH_ROM(DS18X20_2),
    DS18X20_READ_WITH_ROM(DS18X20_2),
#endif
};
uint8_t response[DS18X20_SP_SIZE];


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


const uint8_t* command;
uint8_t current_sensor = DS18X20_SENSOR_COUNT - 1;

void temperature_reader__thread__run(void) {
    VT_BEGIN(temperature_reader__thread, temperature_reader__thread__ip);
    timer0__overflow__interrupt__pending__clear();
    for (;;) {
        if (++current_sensor == DS18X20_SENSOR_COUNT) {
            current_sensor = 0;
            command = commands;
        }

        led1__set(1);
        led2__set(1);

        onewire__command(DS18X20_COMMAND_SIZE, 0, command, 0);
        do {
            VT_YIELD(temperature_reader__thread, temperature_reader__thread__ip);
            onewire__thread__run();
        }
        while (onewire__thread__is_alive());
        command += DS18X20_COMMAND_SIZE;

        led1__set(1);
        led2__set(0);

        onewire__thread__delay_counter = 46;
        timer0__conf__set(TIMER0_CONF_PRESCALER_1024|TIMER0_CONF_WGM_NORMAL);
        for (;;) {
            VT_YIELD(temperature_reader__thread, temperature_reader__thread__ip);
            timer0__overflow__interrupt__pending__clear();
            if (--onewire__thread__delay_counter == 0) break;
        }

        led1__set(0);
        led2__set(1);

        onewire__command(DS18X20_COMMAND_SIZE, sizeof(response), command, response);
        do {
            VT_YIELD(temperature_reader__thread, temperature_reader__thread__ip);
            onewire__thread__run();
        }
        while (onewire__thread__is_alive());
        command += DS18X20_COMMAND_SIZE;

        led1__set(0);
        led2__set(0);

        temperature_reader__readings[current_sensor] = (response[0] | (response[1] << 8)) << 4;
        temperature_reader__readings__on_changed();
    }
    VT_UNREACHEABLE_END(temperature_reader__thread);
}

