// =============================================================================
// Temperature Reader Service
//
// This service continuously reads temperature from a DS18X20 1-wire sensor.
// It uses virtual threads (vthreads) to perform non-blocking operations,
// allowing the main program to continue execution while temperature readings
// are being acquired.
//
// The process works in a continuous loop:
// 1. Send a CONVERT_T command to trigger temperature conversion
// 2. Wait for the conversion to complete (750ms for DS18B20)
// 3. Send a READ command to retrieve the temperature data
// 4. Process and store the temperature reading
// 5. Repeat
//
// Uses 1-wire client functions for communication with the sensor.
// =============================================================================

#include "services/temperature_reader.h"
#include "services/comm/onewire_client.h"
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/timer0.h"


#define OW_SKIP_ROM         0xCC
#define DS18X20_CONVERT_T   0x44
#define DS18X20_READ        0xBE
#define DS18X20_SP_SIZE     9

uint16_t temperature_reader__reading;

uint8_t command_convert[] = {OW_SKIP_ROM, DS18X20_CONVERT_T};
uint8_t command[] = {OW_SKIP_ROM, DS18X20_READ};
uint8_t response[DS18X20_SP_SIZE];


/** Instruction pointer */
#ifdef TEMPERATURE_READER__THREAD__IP__REG
register void* temperature_reader__thread__ip asm(QUOTE(TEMPERATURE_READER__THREAD__IP__REG));
#else
volatile void *temperature_reader__thread__ip;
#endif


volatile uint8_t onewire__thread__delay_counter;


// Helper function to request temperature conversion
void temperature_reader__conversion_request(void) {
    onewire__transaction__setup((uint8_t) sizeof(command_convert), 0, command_convert, 0);
    onewire__transaction__run();
}


// Helper function to wait for conversion to complete
void temperature_reader__conversion_await(void) {
    onewire__thread__delay_counter = TEMPERATURE_READER__CONVERSION_DELAY_COUNT;
    timer0__conf__set(TIMER0_CONF_PRESCALER_1024|TIMER0_CONF_WGM_NORMAL);
}


// Helper function to read the converted temperature
void temperature_reader__conversion_read(void) {
    onewire__transaction__setup(sizeof(command), sizeof(response), command, response);
    onewire__transaction__run();
}


// Helper function to report the temperature reading
void temperature_reader__conversion_report(void) {
    temperature_reader__reading = (response[0] | (response[1] << 8)) << 4;
    temperature_reader__reading__on_changed();
}


void temperature_reader__thread__start(void) {
    VT_INIT(temperature_reader__thread, temperature_reader__thread__ip);
    timer0__conf__set(TIMER0_CONF_PRESCALER_1024|TIMER0_CONF_WGM_NORMAL);
}

bool temperature_reader__thread__is_runnable(void) {
    return timer0__overflow__interrupt__pending__get();
}

/**
 * Continuously read temperature from 1-wire sensor.
 * 1-wire transactions "unrolled" to prevent function calling and save on register usage.
 * TODO: wait between conversions? error handling? crc check?
 */
void temperature_reader__thread__run(void) {
    VT_BEGIN(temperature_reader__thread, temperature_reader__thread__ip);
    timer0__overflow__interrupt__pending__clear();
    for (;;) {
        __asm__ __volatile__( "temperature_reader__thread__conversion_request:");
        temperature_reader__conversion_request();
        do {
            VT_YIELD(temperature_reader__thread, temperature_reader__thread__ip);
            onewire__thread__run();
        }
        while (onewire__thread__is_alive());

        __asm__ __volatile__( "temperature_reader__thread__conversion_await:");
        temperature_reader__conversion_await();
        for (;;) {
            VT_YIELD(temperature_reader__thread, temperature_reader__thread__ip);
            timer0__overflow__interrupt__pending__clear();
            if (--onewire__thread__delay_counter == 0) break;
        }

        __asm__ __volatile__( "temperature_reader__thread__conversion_read:");
        temperature_reader__conversion_read();
        do {
            VT_YIELD(temperature_reader__thread, temperature_reader__thread__ip);
            onewire__thread__run();
        }
        while (onewire__thread__is_alive());

        __asm__ __volatile__( "temperature_reader__thread__conversion_report:");
        temperature_reader__conversion_report();
    }
    VT_UNREACHEABLE_END(temperature_reader__thread);
}

